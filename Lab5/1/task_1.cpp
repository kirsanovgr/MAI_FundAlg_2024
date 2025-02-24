#include <iostream>
#include <bitset>

class binary_int {
private:
    int value;

    static int bitwise_add(int a, int b) {
        while (b != 0) {
            int carry = a & b;
            a = a ^ b;
            b = carry << 1;
        }
        return a;
    }

    static int bitwise_subtract(int a, int b) {
        return bitwise_add(a, bitwise_add(~b, 1));
    }

    static int bitwise_multiply(int a, int b) {
        int result = 0;
        while (b != 0) {
            if (b & 1) {
                result = bitwise_add(result, a);
            }
            a <<= 1;
            b >>= 1;
        }
        return result;
    }

public:
    binary_int(int val = 0) : value(val) {}

    binary_int operator-() const {
        return binary_int(~value + 1);
    }

    binary_int& operator++() {
        value = bitwise_add(value, 1);
        return *this;
    }

    binary_int operator++(int) {
        binary_int temp = *this;
        ++(*this);
        return temp;
    }

    binary_int& operator--() {
        value = bitwise_subtract(value, 1);
        return *this;
    }

    binary_int operator--(int) {
        binary_int temp = *this;
        --(*this);
        return temp;
    }

    binary_int& operator+=(const binary_int& other) {
        value = bitwise_add(value, other.value);
        return *this;
    }

    binary_int operator+(const binary_int& other) const {
        return binary_int(bitwise_add(value, other.value));
    }

    binary_int& operator-=(const binary_int& other) {
        value = bitwise_subtract(value, other.value);
        return *this;
    }

    binary_int operator-(const binary_int& other) const {
        return binary_int(bitwise_subtract(value, other.value));
    }

    binary_int& operator*=(const binary_int& other) {
        value = bitwise_multiply(value, other.value);
        return *this;
    }

    binary_int operator*(const binary_int& other) const {
        return binary_int(bitwise_multiply(value, other.value));
    }

    binary_int& operator<<=(int n) {
        value <<= n;
        return *this;
    }

    binary_int operator<<(int n) const {
        return binary_int(value << n);
    }

    binary_int& operator>>=(int n) {
        value >>= n;
        return *this;
    }

    binary_int operator>>(int n) const {
        return binary_int(value >> n);
    }

    std::pair<binary_int, binary_int> split() const {
        int half_size = sizeof(int) * 8 / 2;
        int high = value >> half_size;
        int low = value & ((1 << half_size) - 1);
        return {binary_int(high), binary_int(low)};
    }

    friend std::ostream& operator<<(std::ostream& os, const binary_int& num) {
        std::bitset<sizeof(num.value) * 8> bits(num.value);
        os << bits;
        return os;
    }

};

int main() {
    int val1, val2;
    std::cout << "Enter the first number: ";
    std::cin >> val1;

    std::cout << "Enter the second number: ";
    std::cin >> val2;

    binary_int a(val1), b(val2);
    binary_int c = a + b;
    binary_int d = a - b;
    binary_int e = a * b;

    std::cout << "a + b = " << c << std::endl;
    std::cout << "a - b = " << d << std::endl;
    std::cout << "a * b = " << e << std::endl;

    a++;
    std::cout << "a++ = " << a << std::endl;

    --b;
    std::cout << "--b = " << b << std::endl;

    std::pair<binary_int, binary_int> split_result = a.split();
    std::cout << "a split: high = " << split_result.first << ", low = " << split_result.second << std::endl;

    a <<= 2;
    std::cout << "a << 2 = " << a << std::endl;

    b >>= 1;
    std::cout << "b >> 1 = " << b << std::endl;

    return 0;
}
