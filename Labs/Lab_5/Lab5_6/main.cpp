#include <iostream>
#include "6.cpp"

int main() {
    vector v1(5, 1.0); // Вектор из 5 элементов со значением 1.0
    vector v2(3, 2.0); // Вектор из 3 элементов со значением 2.0

    v1.push_back(3.5);  // Добавление элемента
    v1.insert(2, 4.5);  // Вставка элемента
    v1.pop_back();      // Удаление последнего элемента
    v1.erase(0);        // Удаление элемента с индексом 0

    std::cout << "v1: ";
    for (auto it = v1.begin(); it != v1.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "v1 size: " << v1.size() << ", capacity: " << v1.capacity() << std::endl;

    std::cout << "Comparison: " << (v1 == v2 ? "Equal" : "Not equal") << std::endl;

    return 0;
}
