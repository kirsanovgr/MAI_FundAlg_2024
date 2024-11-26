#include "ex3.hpp"
int main(){
	logical_values_array a(28);
	logical_values_array b(13);
	std::cout << a << std::endl;
	std::cout << b << std::endl;
	std::cout << ~a << std::endl;
	std::cout << (a & b) << std::endl;
	std::cout << (a | b) << std::endl;
	std::cout << (a ^ b) << std::endl;
	std::cout << (a <= b) << std::endl;
	std::cout << (a > b) << std::endl;
	std::cout << (a == b) << std::endl;
	std::cout << a.pierce_arrow(b) << std::endl;
	std::cout << a.sheffer_stroke(b) << std::endl;


}