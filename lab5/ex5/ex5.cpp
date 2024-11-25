#include "ex5.h"



std::string cdecl_translate(std::string input){
	std::regex regex(R"(^(\w+)\s*(\**)\s*(\(\s*(\*+)\s*(\w+)(\[(\s*\d+)\s*\])?\)\s*\(((\w+)(\**))\))?(\w+\s*(\[\s*(\d+)\s*\])?)?(\w+\s*(\[\s*(\d+)\s*\])?)?)");
	std::string::iterator end_pos = std::remove(input.begin(), input.end(), ' ');
	input.erase(end_pos, input.end());
	end_pos = std::remove(input.begin(), input.end(), '\t');
	input.erase(end_pos, input.end());

	std::string result = "declare ";
	std::smatch m;
	if(std::regex_search(input, m, regex)){
		for(const auto  & el : m){
			std::cout << el << std::endl;

		}
	} else{
		return std::string {"Syntax error at position 0"};
	}
	return input;
}