#include "vector.h"
#include <iostream>

int main() {
    try {
        vector v1(5, 1.0);
        vector v2 = {2.0, 3.0, 4.0};

        v1.push_back(6.0);
        v1.insert(2, 2.5);
        v1.erase(3);

        std::cout << "v1: ";
        for (const auto& elem : v1) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;

        std::cout << "v2: ";
        for (const auto& elem : v2) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;

#if __cplusplus >= 202002L
        std::cout << "v1 <=> v2: " << (v1 <=> v2 < 0 ? "less" : (v1 <=> v2 > 0 ? "greater" : "equal")) << std::endl;
#else
        std::cout << "v1 == v2: " << (v1 == v2) << std::endl;
        std::cout << "v1 < v2: " << (v1 < v2) << std::endl;
        std::cout << "v1 <= v2: " << (v1 <= v2) << std::endl;
        std::cout << "v1 > v2: " << (v1 > v2) << std::endl;
        std::cout << "v1 >= v2: " << (v1 >= v2) << std::endl;
#endif

    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}