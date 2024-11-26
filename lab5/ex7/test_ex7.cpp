#include <gtest/gtest.h>

#include <ctime>

#include "ex7.hpp"

// Тесты для класса Product
TEST(ProductTest, Constructor) {
	Product product("Test Product", 1, 1.0, 10.0, 30);
	EXPECT_EQ(product.get_name(), "Test Product");
	EXPECT_EQ(product.get_id(), 1);
	EXPECT_EQ(product.get_weight(), 1.0);
	EXPECT_EQ(product.get_price(), 10.0);
}

TEST(ProductTest, CopyConstructor) {
	Product product1("Test Product", 1, 1.0, 10.0, 30);
	Product product2(product1);
	EXPECT_EQ(product2.get_name(), "Test Product");
	EXPECT_EQ(product2.get_id(), 1);
	EXPECT_EQ(product2.get_weight(), 1.0);
	EXPECT_EQ(product2.get_price(), 10.0);
}

TEST(ProductTest, AssignmentOperator) {
	Product product1("Test Product", 1, 1.0, 10.0, 30);
	Product product2("Another Product", 2, 2.0, 20.0, 60);
	product2 = product1;
	EXPECT_EQ(product2.get_name(), "Test Product");
	EXPECT_EQ(product2.get_id(), 1);
	EXPECT_EQ(product2.get_weight(), 1.0);
	EXPECT_EQ(product2.get_price(), 10.0);
}

TEST(ProductTest, CalculateStorageFee) {
	Product product("Test Product", 1, 1.0, 10.0, 30);
	EXPECT_EQ(product.calculateStorageFee(), 1.0 * DEFAULT_PRICE_PRODUCT_PLACE);
}

// Тесты для класса PerishableProduct
TEST(PerishableProductTest, Constructor) {
	time_t expirationDate = time(0) + 7 * 24 * 60 * 60;
	PerishableProduct product("Perishable Product", 1, 1.0, 10.0, 30, expirationDate);
	EXPECT_EQ(product.get_name(), "Perishable Product");
	EXPECT_EQ(product.get_id(), 1);
	EXPECT_EQ(product.get_weight(), 1.0);
	EXPECT_EQ(product.get_price(), 10.0);
	EXPECT_EQ(product.getExpirationDate(), expirationDate);
}

TEST(PerishableProductTest, CalculateStorageFee) {
	time_t expirationDate = time(0) + 7 * 24 * 60 * 60;
	PerishableProduct product("Perishable Product", 1, 1.0, 10.0, 30, expirationDate);
	double daysBefore = difftime(expirationDate, time(0)) / 60 / 60 / 24;
	double expectedFee = 1.0 * DEFAULT_PRICE_PRODUCT_PLACE * (1 + (30 - daysBefore) * DEFAULT_INCREASE_PERISHABLE_PRODUCT);
	EXPECT_EQ(product.calculateStorageFee(), expectedFee);
}

// Тесты для класса ElectronicProduct
TEST(ElectronicProductTest, Constructor) {
	ElectronicProduct product("Electronic Product", 1, 1.0, 10.0, 30, 12, 65);
	EXPECT_EQ(product.get_name(), "Electronic Product");
	EXPECT_EQ(product.get_id(), 1);
	EXPECT_EQ(product.get_weight(), 1.0);
	EXPECT_EQ(product.get_price(), 10.0);
}

// Тесты для класса BuildingMaterial
TEST(BuildingMaterialTest, Constructor) {
	BuildingMaterial product("Building Material", 1, 1.0, 10.0, 30, 1.5);
	EXPECT_EQ(product.get_name(), "Building Material");
	EXPECT_EQ(product.get_id(), 1);
	EXPECT_EQ(product.get_weight(), 1.0);
	EXPECT_EQ(product.get_price(), 10.0);
}

TEST(BuildingMaterialTest, CalculateStorageFee) {
	BuildingMaterial product("Building Material", 1, 1.0, 10.0, 30, 1.5);
	EXPECT_EQ(product.calculateStorageFee(), 1.0 * DEFAULT_PRICE_PRODUCT_PLACE * 1.5);
}

// Тесты для класса Warehouse
TEST(WarehouseTest, AddProduct) {
	Warehouse warehouse;
	PerishableProduct product("Perishable Product", 1, 1.0, 10.0, 30, time(0) + 7 * 24 * 60 * 60);
	warehouse += product;
	EXPECT_EQ(warehouse[1]->get_name(), "Perishable Product");
}

TEST(WarehouseTest, RemoveProduct) {
	Warehouse warehouse;
	PerishableProduct product("Perishable Product", 1, 1.0, 10.0, 30, time(0) + 7 * 24 * 60 * 60);
	warehouse += product;
	warehouse -= 1;
	EXPECT_EQ(warehouse[1], nullptr);
}

TEST(WarehouseTest, CalculateTotalStorageFee) {
	Warehouse warehouse;
	PerishableProduct product1("Perishable Product 1", 1, 1.0, 10.0, 30, time(0) + 7 * 24 * 60 * 60);
	ElectronicProduct product2("Electronic Product 2", 2, 2.0, 20.0, 60, 12, 65);
	warehouse += product1;
	warehouse += product2;
	double expectedFee = 0.53;
	EXPECT_EQ(warehouse.calculateTotalStorageFee(), expectedFee);
}

TEST(WarehouseTest, GetProductsByCategory) {
	Warehouse warehouse;
	PerishableProduct product1("Perishable Product", 1, 1.0, 10.0, 30, time(0) + 7 * 24 * 60 * 60);
	ElectronicProduct product2("Electronic Product", 2, 1.0, 10.0, 30, 12, 65);
	warehouse += product1;
	warehouse += product2;
	std::vector<Product*> products = warehouse.get_products_by_category("PerishableProduct");
	EXPECT_EQ(products.size(), 1);
	EXPECT_EQ(products[0]->get_name(), "Perishable Product");
}

TEST(WarehouseTest, GetExpiringProducts) {
	Warehouse warehouse;
	time_t expirationDate = time(0) + 7 * 24 * 60 * 60;
	PerishableProduct product1("Perishable Product", 1, 1.0, 10.0, 30, expirationDate);
	warehouse += product1;
	std::vector<PerishableProduct*> expiringProducts = warehouse.getExpiringProducts(10);
	EXPECT_EQ(expiringProducts.size(), 1);
	EXPECT_EQ(expiringProducts[0]->get_name(), "Perishable Product");
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}