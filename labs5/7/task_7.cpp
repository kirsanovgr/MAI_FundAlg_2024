#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <stdexcept>

class Product {
public:
    Product(const std::string& name, int id, double weight, double price, int shelfLife)
        : name(name), id(id), weight(weight), price(price), shelfLife(shelfLife) {}

    virtual ~Product() = default;

    virtual double calculateStorageFee() const {
        return weight * 0.1;
    }

    virtual void displayInfo() const {
        std::cout << "Name: " << name << ", ID: " << id << ", Weight: " << weight << " kg"
                  << ", Price: $" << price << ", Shelf Life: " << shelfLife << " days\n";
    }

    Product(const Product& other) = default;
    Product& operator=(const Product& other) = default;

    int getId() const { return id; }
    int getShelfLife() const { return shelfLife; }

protected:
    std::string name;
    int id;
    double weight;
    double price;
    int shelfLife;
};

class PerishableProduct : public Product {
public:
    PerishableProduct(const std::string& name, int id, double weight, double price, int shelfLife, const std::string& expirationDate)
        : Product(name, id, weight, price, shelfLife), expirationDate(expirationDate) {}

    double calculateStorageFee() const override {
        return weight * 0.2;
    }

    void displayInfo() const override {
        Product::displayInfo();
        std::cout << "Expiration Date: " << expirationDate << "\n";
    }

private:
    std::string expirationDate;
};

class ElectronicProduct : public Product {
public:
    ElectronicProduct(const std::string& name, int id, double weight, double price, int shelfLife, int warrantyPeriod, int powerRating)
        : Product(name, id, weight, price, shelfLife), warrantyPeriod(warrantyPeriod), powerRating(powerRating) {}

    void displayInfo() const override {
        Product::displayInfo();
        std::cout << "Warranty Period: " << warrantyPeriod << " months, Power Rating: " << powerRating << "W\n";
    }

private:
    int warrantyPeriod;
    int powerRating;
};

class BuildingMaterial : public Product {
public:
    BuildingMaterial(const std::string& name, int id, double weight, double price, int shelfLife, bool flammability)
        : Product(name, id, weight, price, shelfLife), flammability(flammability) {}

    double calculateStorageFee() const override {
        return flammability ? weight * 0.3 : weight * 0.1;
    }

    void displayInfo() const override {
        Product::displayInfo();
        std::cout << "Flammability: " << (flammability ? "Yes" : "No") << "\n";
    }

private:
    bool flammability;
};

class Warehouse {
public:
    void addProduct(std::unique_ptr<Product> product) {
        inventory.push_back(std::move(product));
    }

    void removeProductById(int id) {
        inventory.erase(std::remove_if(inventory.begin(), inventory.end(),
            [id](const std::unique_ptr<Product>& product) { return product->getId() == id; }), inventory.end());
    }

    Product* getProductById(int id) const {
        for (const auto& product : inventory) {
            if (product->getId() == id) {
                return product.get();
            }
        }
        return nullptr;
    }

    double calculateTotalStorageFee() const {
        double totalFee = 0;
        for (const auto& product : inventory) {
            totalFee += product->calculateStorageFee();
        }
        return totalFee;
    }

    std::vector<Product*> getExpiringProducts(int days) const {
        std::vector<Product*> expiringProducts;
        for (const auto& product : inventory) {
            auto perishableProduct = dynamic_cast<PerishableProduct*>(product.get());
            if (perishableProduct && perishableProduct->getShelfLife() <= days) {
                expiringProducts.push_back(perishableProduct);
            }
        }
        return expiringProducts;
    }

    void displayInventory() const {
        std::cout << "Warehouse Inventory:\n";
        for (const auto& product : inventory) {
            product->displayInfo();
        }
    }

    Warehouse& operator+=(std::unique_ptr<Product> product) {
        addProduct(std::move(product));
        return *this;
    }

    Warehouse& operator-=(int id) {
        removeProductById(id);
        return *this;
    }

    Product* operator[](int id) const {
        return getProductById(id);
    }

    friend std::ostream& operator<<(std::ostream& os, const Warehouse& warehouse) {
        warehouse.displayInventory();
        return os;
    }

private:
    std::vector<std::unique_ptr<Product>> inventory;
};

int main() {
    Warehouse warehouse;
    warehouse += std::make_unique<PerishableProduct>("Cheese", 1, 0.5, 4.5, 14, "2024-12-20");
    warehouse += std::make_unique<ElectronicProduct>("Laptop", 2, 2.5, 1500, 365, 24, 65);
    warehouse += std::make_unique<ElectronicProduct>("Smartphone", 3, 0.3, 800, 365, 12, 15);
    warehouse += std::make_unique<BuildingMaterial>("brick", 4, 30.0, 200, 365, false);

    std::cout << warehouse;

    std::cout << "Total Storage Fee: " << warehouse.calculateTotalStorageFee() << "\n";

    auto expiringProducts = warehouse.getExpiringProducts(10);
    std::cout << "Expiring Products within 10 days:\n";
    for (const auto& product : expiringProducts) {
        product->displayInfo();
    }

    warehouse -= 1;
    std::cout << "\nAfter removing product with ID 1:\n";
    std::cout << warehouse;

    Product* product = warehouse[2];
    if (product) {
        std::cout << "\nProduct with ID 2:\n";
        product->displayInfo();
    } else {
        std::cout << "\nProduct with ID 2 not found.\n";
    }

    return 0;
}