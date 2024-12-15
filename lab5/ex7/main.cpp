#include "ex7.hpp"

int main(){
	Warehouse warehouse;
	PerishableProduct product1 = {"Perishable Product", 1, 1.0, 10.0, 30, time(0) + 7 * 24 * 60 * 60};
	ElectronicProduct product2 = ElectronicProduct("Electronic Product", 2, 1.0, 10.0, 30, 12, 65);
	warehouse += product2;
	warehouse.displayInventory();
}