
#include "ex3.hpp"
unsigned int logical_values_array::get_value() const { return value; }
bool logical_values_array::equals(const logical_values_array& first, const logical_values_array& second) {
	return second.get_value() == first.get_value();
}
void logical_values_array::to_char_arr(char* result) const {
	std::memset(result, '\0', sizeof(unsigned int) * 8 + 1);
	for (int i = sizeof(unsigned int) * 8 - 1, j = 0; i >= 0; --i, j++) {
		result[j] = (char)((char)((value >> i) & 1) + '0');
	}

}
bool logical_values_array::get_bit(unsigned int index) const {
	if (index >= sizeof(unsigned int) * 8) {
		throw std::range_error("incorrect index");
	}
	return (value & (1 << (sizeof(unsigned int) * 8 - index - 1)));
}
logical_values_array logical_values_array::operator~() const { return logical_values_array{~value}; }
logical_values_array logical_values_array::operator&(const logical_values_array& second) const {
	return value & second.get_value();
}
logical_values_array logical_values_array::operator|(const logical_values_array& second) const {
	return ~logical_values_array{~(*this) & ~(second)};
}
logical_values_array logical_values_array::operator^(const logical_values_array& second) const {
	return logical_values_array{(((~(*this)) & second) | (*this & (~second)))};
}
logical_values_array logical_values_array::operator<=(const logical_values_array& second) const {
	return logical_values_array{(~(*this)) | second};
}
logical_values_array logical_values_array::operator>(const logical_values_array& second) const {
	return ~(*this <= second);
}
logical_values_array logical_values_array::operator==(const logical_values_array& second) const {
	return logical_values_array{((~(*this)) | second) & (*this | (~(second)))};
}
logical_values_array logical_values_array::pierce_arrow(const logical_values_array& second) const {
	return logical_values_array{~(*this | second)};
}
logical_values_array logical_values_array::sheffer_stroke(const logical_values_array& second) const {
	return logical_values_array{~(*this & second)};
}

logical_values_array::logical_values_array(const logical_values_array& ar) {
	value = ar.get_value();
}

logical_values_array& logical_values_array::operator=(const logical_values_array& ar){
	if(&ar != this){
		value = ar.get_value();
	}
	return *this;
}

std::ostream& operator<<(std::ostream& out, const logical_values_array& el) {
	for (int i = sizeof(unsigned int) * 8 - 1; i >= 0; --i) {
		out << ((el.get_value() >> i) & 1);
	}
	return out;
}