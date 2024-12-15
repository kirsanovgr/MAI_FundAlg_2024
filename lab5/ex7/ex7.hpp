#pragma once

#include <algorithm>
#include <ctime>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <memory>

#define DEFAULT_PRICE_PRODUCT_PLACE 0.1
#define DEFAULT_INCREASE_PERISHABLE_PRODUCT 0.1

class incorrect_data_product : std::exception {};
class flammability_must_be_less_than_null : std::exception {};
class repeated_id : std::exception {};

class Product {
   private:
	void is_correct_product() const;

   protected:
	std::string name;
	size_t id;
	double weight;
	double price;
	unsigned int storage_days;

   public:
	Product(const std::string& _name, size_t _id, double _weight, double _price, unsigned int _storage_days);
	Product(const Product& product);
	~Product();

	size_t get_id() const;
	std::string get_name() const;
	double get_weight() const;
	double get_price() const;

	Product& operator=(const Product& product);

	virtual std::string get_category() const;
	virtual void displayInfo() const;
	virtual double calculateStorageFee() const;
};

class PerishableProduct : public Product {
   private:
	time_t expirationDate;

   public:
	PerishableProduct(const std::string& name, size_t id, double weight, double price, unsigned int storage_days,
	                  time_t expiration_date);

	PerishableProduct(const Product& product, const PerishableProduct& perishableProduct);
	PerishableProduct & operator=(const PerishableProduct & perishableProduct);


	time_t getExpirationDate() const;
	std::string get_category() const override;
	double calculateStorageFee() const override;
};

class ElectronicProduct : public Product {
   private:
	size_t warrantyPeriod;
	size_t powerRating;

   public:
	ElectronicProduct(const std::string& name, int id, double weight, double price, unsigned int storageDays,
	                  size_t warrantyPeriod, size_t powerRating);

	ElectronicProduct(const Product& product, const ElectronicProduct& electronicProduct);
	ElectronicProduct & operator=(const ElectronicProduct & electronicProduct);

	std::string get_category() const override;
	void displayInfo() const override;
};

class BuildingMaterial : public Product {
   private:
	double flammability = 0;

   public:
	BuildingMaterial(const std::string& name, size_t id, double weight, double price, unsigned int storageDays,
	                 double flammability);

	BuildingMaterial(const Product& product, const BuildingMaterial& buildingMaterial);

	BuildingMaterial& operator=(const BuildingMaterial & buildingMaterial);

	std::string get_category() const override;
	double calculateStorageFee() const override;
};

class Warehouse {
   private:
	std::map<size_t, Product*> products;

   public:


	std::map<size_t, Product*> get_products() const;
	std::vector<Product*> get_products_by_category(const std::string& category) const;
	std::vector<PerishableProduct*> getExpiringProducts(size_t days) const;
	void displayInventory() const;

	Warehouse& operator+=(Product& product) &;
	Warehouse& operator-=(size_t id) &;
	Product* operator[](size_t id) &;
	double calculateTotalStorageFee() const;
};

std::ostream& operator<<(std::ostream& ostream, const Warehouse& warehouse);

