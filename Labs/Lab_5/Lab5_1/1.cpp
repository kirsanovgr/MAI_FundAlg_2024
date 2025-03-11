#include "1.hpp"
#include <cstdlib> // abs()

// Конструктор
binary_int::binary_int(int v) : value(v) {}

binary_int binary_int::operator-() const {
    return binary_int(~value + 1);
}

// Префиксный инкремент
binary_int &binary_int::operator++() {
    value = add(value, 1);
    return *this;
}

// Постфиксный инкремент
binary_int binary_int::operator++(int) {
    binary_int temp = *this;
    ++(*this);
    return temp;
}

// Префиксный декремент
binary_int &binary_int::operator--() {
    value = add(value, -1);
    return *this;
}

// Постфиксный декремент
binary_int binary_int::operator--(int) {
    binary_int temp = *this;
    --(*this);
    return temp;
}

binary_int &binary_int::operator+=(const binary_int &other) {
    value = add(value, other.value);
    return *this;
}

binary_int binary_int::operator+(const binary_int &other) const {
    return binary_int(add(value, other.value));
}

binary_int &binary_int::operator-=(const binary_int &other) {
    value = add(value, -other.value);
    return *this;
}

binary_int binary_int::operator-(const binary_int &other) const {
    return binary_int(add(value, -other.value));
}

binary_int &binary_int::operator*=(const binary_int &other) {
    value = multiply(value, other.value);
    return *this;
}

binary_int binary_int::operator*(const binary_int &other) const {
    return binary_int(multiply(value, other.value));
}

binary_int &binary_int::operator<<=(int shift) {
    value <<= shift;
    return *this;
}

binary_int binary_int::operator<<(int shift) const {
    return binary_int(value << shift);
}

binary_int &binary_int::operator>>=(int shift) {
    value >>= shift;
    return *this;
}

binary_int binary_int::operator>>(int shift) const {
    return binary_int(value >> shift);
}

std::pair<binary_int, binary_int> binary_int::split_bits() const {
    int total_bits = sizeof(int) * 8;
    int mid = total_bits / 2;

    int upper = value & (~((1 << mid) - 1)); // Старшие биты
    int lower = value & ((1 << mid) - 1);   // Младшие биты

    return {binary_int(upper), binary_int(lower)};
}

// Оператор <<
std::ostream &operator<<(std::ostream &os, const binary_int &obj) {
    for (int i = sizeof(int) * 8 - 1; i >= 0; --i) {
        os << ((obj.value >> i) & 1);
    }
    return os;
}

int binary_int::add(int a, int b) {
    while (b != 0) {
        int carry = a & b;
        a = a ^ b;
        b = carry << 1;
    }
    return a;
}

int binary_int::multiply(int a, int b) {
    int result = 0;
    bool negative = (a < 0) ^ (b < 0);
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
