#include <iostream>
#include <string>
#include <regex>
#include <fstream>

std::string cdecl_translate(const std::string& declaration) {
    std::regex type_regex(R"((int|char|float|double)\s*(.*);)");
    std::smatch match;
    if (!std::regex_match(declaration, match, type_regex)) {
        return "Syntax error: invalid type";
    }

    std::string type = match[1];
    std::string rest = match[2];
    std::string result = "declare ";

    std::regex pointer_regex(R"((\*+)\s*(\w+))");
    std::regex array_regex(R"((\w+)\s*\[\s*(\d*)\s*\])");
    std::regex func_regex(R"(\(\s*\*\s*(\w+)\s*\)\s*\(\s*\))");
    std::regex simple_func_regex(R"((\w+)\s*\(\s*\))");

    if (std::regex_match(rest, match, pointer_regex)) {
        std::string pointers = match[1];
        std::string var_name = match[2];
        if (!std::regex_match(var_name, std::regex(R"([a-zA-Z_]\w*)"))) {
            return "Syntax error: invalid variable name";
        }
        result += var_name + " as ";
        for (char c : pointers) {
            result += "pointer to ";
        }
        result += type;
    } else if (std::regex_match(rest, match, array_regex)) {
        std::string var_name = match[1];
        std::string size = match[2];
        if (!std::regex_match(var_name, std::regex(R"([a-zA-Z_]\w*)"))) {
            return "Syntax error: invalid variable name";
        }
        result += var_name + " as array of " + (size.empty() ? "unknown size" : size) + " elements of " + type;
    } else if (std::regex_match(rest, match, func_regex)) {
        std::string var_name = match[1];
        if (!std::regex_match(var_name, std::regex(R"([a-zA-Z_]\w*)"))) {
            return "Syntax error: invalid variable name";
        }
        result += var_name + " as pointer to function returning " + type;
    } else if (std::regex_match(rest, match, simple_func_regex)) {
        std::string var_name = match[1];
        if (!std::regex_match(var_name, std::regex(R"([a-zA-Z_]\w*)"))) {
            return "Syntax error: invalid variable name";
        }
        result += var_name + " as function returning " + type;
    } else {
        return "Syntax error: invalid declaration";
    }

    return result;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <file_path>" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "Error: could not open file " << argv[1] << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::string result = cdecl_translate(line);
        std::cout << result << std::endl;
    }

    file.close();
    return 0;
}