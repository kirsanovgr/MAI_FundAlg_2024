#include <iostream>
//#include <iomanip>
//#include <limits>
//#include <stdexcept>

class binary_int {
private:
    int value;

public:
    // Конструктор
    binary_int(int v = 0) : value(v) {}

    // Унарный минус
    binary_int operator-() const {
        return binary_int(~value + 1);
    }

    // Префиксный инкремент
    binary_int& operator++() {
        value = add(value, 1);
        return *this;
    }

    // Постфиксный инкремент
    binary_int operator++(int) {
        binary_int temp = *this;
        ++(*this);
        return temp;
    }

    // Префиксный декремент
    binary_int& operator--() {
        value = add(value, -1);
        return *this;
    }

    // Постфиксный декремент
    binary_int operator--(int) {
        binary_int temp = *this;
        --(*this);
        return temp;
    }

    // Оператор +=
    binary_int& operator+=(const binary_int& other) {
        value = add(value, other.value);
        return *this;
    }

    // Оператор +
    binary_int operator+(const binary_int& other) const {
        return binary_int(add(value, other.value));
    }

    // Оператор -=
    binary_int& operator-=(const binary_int& other) {
        value = add(value, -other.value);
        return *this;
    }

    // Оператор -
    binary_int operator-(const binary_int& other) const {
        return binary_int(add(value, -other.value));
    }

    // Оператор *=
    binary_int& operator*=(const binary_int& other) {
        value = multiply(value, other.value);
        return *this;
    }

    // Оператор *
    binary_int operator*(const binary_int& other) const {
        return binary_int(multiply(value, other.value));
    }

    // Оператор <<= 
    binary_int& operator<<=(int shift) {
        value <<= shift;
        return *this;
    }

    // Оператор <<
    binary_int operator<<(int shift) const {
        return binary_int(value << shift);
    }

    // Оператор >>= 
    binary_int& operator>>=(int shift) {
        value >>= shift;
        return *this;
    }

    // Оператор >>
    binary_int operator>>(int shift) const {
        return binary_int(value >> shift);
    }

    // Метод получения двух частей битов
    std::pair<binary_int, binary_int> split_bits() const {
        int total_bits = sizeof(int) * 8;
        int mid = total_bits / 2;

        int upper = value & (~((1 << mid) - 1));       // Сохраняем старшие биты
        int lower = value & ((1 << mid) - 1);         // Сохраняем младшие биты

        return {binary_int(upper), binary_int(lower)};
    }

    // Оператор вставки в поток
    friend std::ostream& operator<<(std::ostream& os, const binary_int& obj) {
        for (int i = sizeof(int) * 8 - 1; i >= 0; --i) {
            os << ((obj.value >> i) & 1);
        }
        return os;
    }

private:
    // Реализация сложения
    static int add(int a, int b) {
        while (b != 0) {
            int carry = a & b;
            a = a ^ b;
            b = carry << 1;
        }
        return a;
    }

    // Реализация умножения
    static int multiply(int a, int b) {
        int result = 0;
        bool negative = (a < 0) ^ (b < 0);  // Определяем знак результата
        a = abs(a);
        b = abs(b);

        while (b != 0) {
            if (b & 1) {
                result = add(result, a);
            }
            a <<= 1;
            b >>= 1;
        }

        return negative ? -result : result;
    }
};

// Демонстрация
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
