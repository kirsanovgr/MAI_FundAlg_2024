#include <iostream>
#include <bitset>
#include <string>
#include <stdexcept>

class logical_values_array {
private:
    unsigned int value;

public:
    explicit logical_values_array(unsigned int v = 0) : value(v) {}

    logical_values_array(const logical_values_array& other) : value(other.value) {}

    logical_values_array& operator=(logical_values_array other) {
        std::swap(value, other.value);
        return *this;
    }

    ~logical_values_array() = default;

    unsigned int get_value() const {
        return value;
    }

    void set_value(unsigned int v) {
        value = v;
    }

    logical_values_array negate() const {
        return logical_values_array(~value);
    }

    logical_values_array conjunction(const logical_values_array& other) const {
        return logical_values_array(value & other.value);
    }

    logical_values_array disjunction(const logical_values_array& other) const {
        return logical_values_array(value | other.value);
    }

    logical_values_array implication(const logical_values_array& other) const {
        return logical_values_array(~value | other.value);
    }

    logical_values_array equivalence(const logical_values_array& other) const {
        return negate().implication(other).conjunction(other.negate().implication(*this));
    }

    logical_values_array modulo_sum(const logical_values_array& other) const {
        return logical_values_array(value ^ other.value);
    }

    logical_values_array pierce_arrow(const logical_values_array& other) const {
        return logical_values_array(~(value | other.value));
    }

    logical_values_array sheffer_stroke(const logical_values_array& other) const {
        return logical_values_array(~(value & other.value));
    }

    static bool equals(const logical_values_array& a, const logical_values_array& b) {
        return a.get_value() == b.get_value();
    }

    bool get_bit(int position) const {
        if (position < 0 || position >= 32) {
            throw std::out_of_range("Position must be between 0 and 31");
        }
        return (value & (1 << position)) != 0;
    }

    std::string to_binary_string() const {
        std::string binary = std::bitset<32>(value).to_string();
        return binary;
    }

    void print() const {
        std::cout << "Value: " << value << " (Binary: " << to_binary_string() << ")" << std::endl;
    }
};

class logical_values_printer {
public:
    static void print_logical_values(const logical_values_array& obj) {
        std::cout << "Value: " << obj.get_value() << " (Binary: " << obj.to_binary_string() << ")" << std::endl;
    }
};

int main() {
    logical_values_array a(5);
    logical_values_array b(3);
    
    logical_values_printer::print_logical_values(a);
    logical_values_printer::print_logical_values(b);

    logical_values_printer::print_logical_values(a.negate());
    logical_values_printer::print_logical_values(a.conjunction(b));
    logical_values_printer::print_logical_values(a.disjunction(b));
    logical_values_printer::print_logical_values(a.implication(b));
    logical_values_printer::print_logical_values(a.equivalence(b));
    logical_values_printer::print_logical_values(a.modulo_sum(b));
    logical_values_printer::print_logical_values(a.pierce_arrow(b));
    logical_values_printer::print_logical_values(a.sheffer_stroke(b));

    std::cout << "a equals b? " << (logical_values_array::equals(a, b) ? "Yes" : "No") << std::endl;

    int pos = 2;
    std::cout << "Bit at position " << pos << " in a: " << a.get_bit(pos) << std::endl;

    return 0;
}
