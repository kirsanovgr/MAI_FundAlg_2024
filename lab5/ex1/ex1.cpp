#include "ex1.hpp"

binary_int::binary_int() { number = 0; }

binary_int::binary_int(int x) { number = x; }

binary_int binary_int::operator-() const { return add(~this->number, 1); }

binary_int binary_int::operator+(binary_int x) const { return add(this->number, x.number); }

binary_int binary_int::operator-(binary_int x) const { return (*this) + (-x); }

binary_int &binary_int::operator+=(binary_int x) {
	this->number = add(this->number, x.number);
	return *this;
}

binary_int &binary_int::operator-=(binary_int x) {
	this->number = add(this->number, (~x.number + 1));
	return *this;
}

binary_int &binary_int::operator*=(binary_int x) {
	int a = this->number;
	int b = x.number;
	int result = 0;

	for (int i = 0; i < 32; ++i) {
		if (b & (1 << i)) {
			result = add(result, a << i);
		}
	}

	this->number = result;
	return *this;
}

binary_int &binary_int::operator++() & {
	this->number = add(this->number, 1);
	return *this;
}

binary_int &binary_int::operator--() & {
	this->number = add(this->number, -1);
	return *this;
}

bool binary_int::operator<(binary_int x) const { return this->number < x.number; }

binary_int binary_int::operator*(binary_int x) const {
	binary_int temp;

	temp.number = 0;
	int a = this->number;
	int b = x.number;

	for (int i = 0; i < 32; ++i) {
		if (b & (1 << i)) {
			temp.number = add(temp.number, a << i);
		}
	}

	return temp;
}

binary_int &binary_int::operator<<=(binary_int x) {
	this->number <<= x.number;
	return *this;
}

binary_int &binary_int::operator>>=(binary_int x) {
	this->number >>= x.number;
	return *this;
}

binary_int binary_int::operator&(binary_int x) const { return this->number & x.number; }

std::ostream &operator<<(std::ostream &stream, binary_int binaryInt) {
	int value = binaryInt.get_number();
	for (int i = (sizeof(int) * 8) - 1; i >= 0; --i) {
		int bit = (value >> i) & 1;
		stream << bit;
	}
	return stream;
}

std::pair<binary_int, binary_int> binary_int::to_parts() const {
	binary_int half_bits = sizeof(int) * 8 / 2;
	binary_int high_bits = ((*this >> half_bits) & (((binary_int)(1) << half_bits) - 1)) << half_bits;
	binary_int low_bits = *this & (((binary_int)(1) << half_bits) - 1);
	return {high_bits, low_bits};
}

binary_int binary_int::operator<<(binary_int x) const { return this->number << x.number; }

binary_int binary_int::operator>>(binary_int x) const { return this->number >> x.number; }

int binary_int::add(int a, int b) {
	int carry = 0;

	while (b != 0) {
		carry = a & b;
		a ^= b;
		b = carry << 1;
	}

	return a;
}
int binary_int::get_number() const { return number; }
binary_int binary_int::operator++(int) {
	binary_int tmp = *this;
	++(*this);
	return tmp;
}

binary_int binary_int::operator--(int) {
	binary_int tmp = *this;
	--(*this);
	return tmp;
}

int binary_int::sub(int a, int b) {
	b = add(~b, 1);
	return add(a, b);
}