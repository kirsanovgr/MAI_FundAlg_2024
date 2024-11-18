#include "ex2.h"


int main(){
	std::vector<std::byte> byte_vector;

	// Добавляем байты в вектор
	byte_vector.push_back(std::byte{0x01});
	byte_vector.push_back(std::byte{0x02});
	byte_vector.push_back(std::byte{0x03});

	encoder enc(byte_vector);
	try{
		enc.encode("input_file", "output", true);
		enc.encode("output", "rr.txt", false);
	} catch (const not_open_stream&){
		std::cout << "File didn't open\n";
		return 1;
	}
}