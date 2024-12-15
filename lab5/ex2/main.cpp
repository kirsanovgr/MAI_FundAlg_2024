#include "ex2.hpp"

int main(){
	std::vector<uint8_t> byte_vector;

	// Добавляем байты в вектор
	byte_vector.push_back(123);
	byte_vector.push_back(12);
	byte_vector.push_back(32);

	encoder enc(byte_vector);
	try {
		enc.encode("input_file", "output", true);
		enc.encode("output", "rr.txt", false);
	} catch (const std::invalid_argument &) {
		std::cout << "File didn't open\n";
		return 1;
	}
}