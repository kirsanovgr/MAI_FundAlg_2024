#include "1.hpp"
#include <iostream>

int main() {
	binary_int a(10);
	binary_int b(3);

	std::cout << "a: " << a << "\nb: " << b << "\n";

	binary_int c = a + b;
	std::cout << "a + b: " << c << "\n";

	c = a - b;
	std::cout << "a - b: " << c << "\n";

	c = a * b;
	std::cout << "a * b: " << c << "\n";

	++a;
	std::cout << "++a: " << a << "\n";

	--b;
	std::cout << "--b: " << b << "\n";

	auto [upper, lower] = a.split_bits();
	std::cout << "Upper bits: " << upper << "\n";
	std::cout << "Lower bits: " << lower << "\n";

	return 0;
}