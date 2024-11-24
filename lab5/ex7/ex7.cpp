#include "ex7.h"

void Product::is_correct_product() const {
	if (name.empty() or weight <= 0 or price < 0) {
		throw incorrect_data_product();
	}
}
Product::Product(const std::string& _name, size_t _id, double _weight, double _price, unsigned int _storage_days)
    : name(_name), id(_id), weight(_weight), price(_price), storage_days(_storage_days) {
	is_correct_product();
}
Product::Product(const Product& product)
    : name(product.name),
      id(product.id),
      weight(product.weight),
      price(product.price),
      storage_days(product.storage_days) {
	is_correct_product();
}
Product& Product::operator=(const Product& product) {
	if (this != &product) {
		name = product.name;
		id = product.id;
		weight = product.weight;
		price = product.price;
		storage_days = product.storage_days;
		is_correct_product();
	}
	return *this;
}
Product::~Product() {
	id = 0;
	weight = 0;
	price = 0;
	storage_days = 0;
	std::destroy(name.begin(), name.end());
}
void Product::displayInfo() const {
	std::cout << "Product: " << name << std::endl;
	std::cout << "Id: " << id << std::endl;
	std::cout << "Weight: " << weight << std::endl;
	std::cout << "Price: " << price << std::endl;
	std::cout << "Shelf life in days: " << storage_days << std::endl;
}

double Product::calculateStorageFee() const { return weight * DEFAULT_PRICE_PRODUCT_PLACE; }

size_t Product::get_id() const { return id; }

std::string Product::get_name() const { return name; }

double Product::get_weight() const { return weight; }
std::string Product::get_category() const { return "Product"; }
double Product::get_price() const { return price; }

double PerishableProduct::calculateStorageFee() const {
	double days_before = difftime(expirationDate, time(0)) / 60 / 60 / 24;
	if (days_before < 0) days_before = 0;
	return Product::calculateStorageFee() * (1 + (storage_days - days_before) * DEFAULT_INCREASE_PERISHABLE_PRODUCT);
}

PerishableProduct::PerishableProduct(const std::string& name, size_t id, double weight, double price,
                                     unsigned int storage_days, time_t expiration_date)
    : Product(name, id, weight, price, storage_days), expirationDate{expiration_date} {}

time_t PerishableProduct::getExpirationDate() const { return expirationDate; }
std::string PerishableProduct::get_category() const { return "PerishableProduct"; }

PerishableProduct::PerishableProduct(const Product& product, const PerishableProduct& perishableProduct)
    : Product(product) {
	storage_days =  perishableProduct.storage_days;
}
PerishableProduct& PerishableProduct::operator=(const PerishableProduct& perishableProduct){
	if(this != &perishableProduct){
		Product{perishableProduct};
		storage_days = perishableProduct.storage_days;
	}
	return *this;
}

ElectronicProduct::ElectronicProduct(const std::string& name, int id, double weight, double price,
                                     unsigned int storageDays, size_t warrantyPeriod, size_t powerRating)
    : Product(name, id, weight, price, storageDays), warrantyPeriod(warrantyPeriod), powerRating(powerRating) {}

void ElectronicProduct::displayInfo() const {
	Product::displayInfo();
	std::cout << "Warranty Period: " << warrantyPeriod << " months\n";
	std::cout << "Power Rating: " << powerRating << " W\n";
}

std::string ElectronicProduct::get_category() const { return "ElectronicProduct"; }

ElectronicProduct::ElectronicProduct(const Product& product, const ElectronicProduct& electronicProduct)
    : Product(product) {
	powerRating = electronicProduct.powerRating;
	warrantyPeriod = electronicProduct.warrantyPeriod;
}
ElectronicProduct& ElectronicProduct::operator=(const ElectronicProduct& electronicProduct) {
	if(this != &electronicProduct){
		Product{electronicProduct};
		warrantyPeriod = electronicProduct.warrantyPeriod;
		powerRating = electronicProduct.powerRating;
	}
	return *this;
}

double BuildingMaterial::calculateStorageFee() const {
	return (flammability > 0) ? Product::calculateStorageFee() * flammability : Product::calculateStorageFee();
}
BuildingMaterial::BuildingMaterial(const std::string& name, size_t id, double weight, double price,
                                   unsigned int storageDays, double flammability)
    : Product(name, id, weight, price, storageDays), flammability(flammability) {
	if (flammability < 0) {
		throw flammability_must_be_less_than_null();
	}
}
std::string BuildingMaterial::get_category() const { return "BuildingMaterial"; }
BuildingMaterial::BuildingMaterial(const Product& product, const BuildingMaterial& buildingMaterial)
    : Product(product) {
	flammability = buildingMaterial.flammability;
}
BuildingMaterial BuildingMaterial::operator=(const BuildingMaterial& buildingMaterial) {
	if(this != &buildingMaterial){
		Product{buildingMaterial};
		flammability = buildingMaterial.flammability;
	}
	return *this;
}

Warehouse& Warehouse::operator+=(const ElectronicProduct& product) & {
	if (products.find(product.get_id()) != products.end()) {
		throw repeated_id();
	}
	products[product.get_id()] = new ElectronicProduct{product};
	return *this;
}

Warehouse& Warehouse::operator+=(const PerishableProduct& product) & {
	if (products.find(product.get_id()) != products.end()) {
		throw repeated_id();
	}
	products[product.get_id()] = new PerishableProduct{product};
	return *this;
}

Warehouse& Warehouse::operator+=(const BuildingMaterial& product) & {
	if (products.find(product.get_id()) != products.end()) {
		throw repeated_id();
	}
	products[product.get_id()] = new BuildingMaterial{product};
	return *this;
}



Warehouse& Warehouse::operator-=(size_t id) & {
	std::map<size_t, Product*>::iterator f = products.find(id);
	if (f != products.end()) {
		delete f->second;
		products.erase(f);
	}
	return *this;
}

Product* Warehouse::operator[](size_t id) & {
	std::map<size_t, Product*>::iterator f = products.find(id);
	if (f == products.end()) {
		return nullptr;
	}
	return (f->second);
}
std::ostream& operator<<(std::ostream& ostream, const Warehouse& warehouse) {
	for (const std::pair<size_t, Product*> pr : warehouse.get_products()) {
		pr.second->displayInfo();
		std::cout << "------------------------\n";
	}

	return ostream;
}

double Warehouse::calculateTotalStorageFee() const {
	double totalFee = 0.0;
	for (const std::pair<size_t, Product*> pair : products) {
		totalFee += pair.second->calculateStorageFee();
	}
	return totalFee;
}

std::vector<Product*> Warehouse::get_products_by_category(const std::string& category) const {
	std::vector<Product*> result;
	for (const std::pair<size_t, Product*> product : products) {
		if (product.second->get_category() == category) {
			result.push_back(product.second);
		}
	}
	return result;
}

std::vector<PerishableProduct*> Warehouse::getExpiringProducts(size_t days) const {
	std::vector<PerishableProduct*> result;
	for (const std::pair<size_t, Product*> pair : products) {
		PerishableProduct* pr = dynamic_cast<PerishableProduct*>(pair.second);
		if (pr) {
			double diff = difftime(time(0), pr->getExpirationDate()) / 60 / 60 / 24;  //  разница в секундах -> в днях
			if (diff < days) {
				result.push_back(pr);
			}
		}
	}
	return result;
}
void Warehouse::displayInventory() const {
	std::map<std::string, std::vector<Product*>> tmp;
	for (const std::pair<size_t, Product*> el : products) {
		tmp[el.second->get_category()].push_back(el.second);
	}
	for (const std::pair<std::string, std::vector<Product*>> category : tmp) {
		std::cout << "Category: " << category.first << std::endl;
		for (const Product * product : category.second) {
			product->displayInfo();
			std::cout << "------------------------\n";
		}
	}
}
std::map<size_t, Product*> Warehouse::get_products() const {
	return products;
}
Warehouse::~Warehouse() {
	for(const std::pair <size_t, Product*> &el : products){
		delete el.second;
	}
}
