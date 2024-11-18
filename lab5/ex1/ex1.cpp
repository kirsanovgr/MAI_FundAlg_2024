#include "ex1.h"

int add(int a, int b) {
	int carry;
	while (b != 0) {
		carry = a & b;
		a ^= b;
		b = carry << 1;
	}
	return a;
}

int sub(int a, int b) {
	b = add(~b, 1);
	return add(a, b);
}

binary_int::binary_int(int number) {
	count_bits = sizeof(int) * 8;
	std::memset(bit_representation, 0, sizeof(int) * 8);
	if (number < 0) {
		number = add(~number, 1);
		bit_representation[0] = true;
	}
	int i = 31;
	while (number > 0) {
		bit_representation[i] = number & 1;
		number = number >> 1;
		i--;
	}
	if (bit_representation[0]) {
		to_reserve_code();
	}
}

binary_int::binary_int(const bool number[sizeof(int) * 8]) {
	count_bits = sizeof(int) * 8;
	for (int i = 0; i < get_count_bits(); i++) {
		bit_representation[i] = number[i];
	}
}

bool *binary_int::get_bit_representation() { return bit_representation; }

binary_int binary_int::operator-() {
	binary_int res{bit_representation};
	res.get_bit_representation()[0] = !(res.get_bit_representation())[0];
	res.to_reserve_code();
	return res;
}

binary_int binary_int::operator+(binary_int &second) {
	bool new_number[this->count_bits];
	bool carry = false;
	int amount = 0;
	for (int i = add(count_bits, -1); i >= 0; i = add(i, -1)) {
		new_number[i] = (bit_representation[i] ^ second.get_bit_representation()[i]) ^ carry;
		if (bit_representation[i]) {
			amount = add(amount, 1);
		}
		if (second.get_bit_representation()[i]) {
			amount = add(amount, 1);
		}
		if (carry) {
			amount = add(amount, 1);
		}
		if (amount > 1) {
			carry = true;
		} else {
			carry = false;
		}
		amount = 0;
	}
	return binary_int{new_number};
}

int binary_int::get_count_bits() const { return this->count_bits; }

void binary_int::to_reserve_code() {
	int i;
	for (i = 1; i < count_bits; ++i) {
		bit_representation[i] = !bit_representation[i];
	}
	i -= 1;
	while (i > 0) {
		if (!bit_representation[i]) {
			bit_representation[i] = true;
			break;
		} else {
			bit_representation[i] = false;
		}
		i--;
	}
}

binary_int binary_int::operator-(binary_int &second) {
	second = -second;
	binary_int new_number = *this + second;
	return binary_int{new_number};
}

binary_int binary_int::operator*(binary_int &second) {
	binary_int tmp_this = *this;
	binary_int tmp_second = second;
	int count = 0;
	if(this->get_bit_representation()[0]){
		tmp_this = -tmp_this;
		count += 1;
	}
	if(second.get_bit_representation()[0]){
		count += 1;
		tmp_second = -tmp_second;
	}


	bool tmp[tmp_this.get_count_bits()];
	std::memmove(tmp, tmp_this.bit_representation, count_bits);
	binary_int tmp_binary_int{tmp};

	bool new_number[tmp_this.get_count_bits()];
	memset(new_number, false, get_count_bits());
	binary_int binary{new_number};


	for (int i = add(get_count_bits(), -1); i >= 0; i--) {
		if (tmp_second.get_bit_representation()[i]) {
			binary = (tmp_binary_int + binary);

		}
		tmp_binary_int <<= 1;
	}
	if(count == 1){
		binary = -binary;
	}

	return binary;
}

binary_int binary_int::operator<<(int shift) {
	if (shift < 0 || shift >= get_count_bits()) {
		return binary_int{0};
	}

	bool new_number[this->get_count_bits()];
	std::memmove(new_number, this->get_bit_representation(), get_count_bits());

	int i;
	for (i = get_count_bits() - shift - 1; i >= 0; i--) {
		new_number[i] = get_bit_representation()[i + shift];
	}

	std::memset(&(new_number[get_count_bits() - shift]), false, shift);

	return binary_int{new_number};
}

binary_int binary_int::operator>>(int shift) {
	if (shift < 0 || shift >= get_count_bits()) {
		return binary_int{0};
	}

	bool new_number[this->get_count_bits()];
	std::memmove(new_number, this->get_bit_representation(), get_count_bits());
	bool fl = false;
	if(new_number[0]){
		fl = true;
	}
	int i;
	for (i = shift; i < get_count_bits(); i++) {
		new_number[i] = get_bit_representation()[i - shift];
	}

	std::memset(new_number, fl, shift);

	return binary_int{new_number};
}

binary_int binary_int::operator<<(binary_int &rhs) {
	if (rhs.get_bit_representation()[0]) {
		return binary_int{0};
	}

	int count = 1;
	bool new_number[this->get_count_bits()];
	std::memmove(new_number, this->get_bit_representation(), get_count_bits());
	binary_int binary{new_number};

	for (int i = get_count_bits() - 1, j = 0; i >= 0; i--, j++) {
		if (rhs.get_bit_representation()[i]) {
			if (j >= 6) {
				return binary_int{0};
			}
			binary = binary << count;
		}
		count *= 2;
	}
	return binary;
}

binary_int binary_int::operator>>(binary_int &rhs) {
	if (rhs.get_bit_representation()[0]) {
		return binary_int{0};
	}

	int count = 1;
	bool new_number[this->get_count_bits()];
	std::memmove(new_number, this->get_bit_representation(), get_count_bits());
	binary_int binary{new_number};

	for (int i = get_count_bits() - 1, j = 0; i >= 0; i--, j++) {
		if (rhs.get_bit_representation()[i]) {
			if (j >= 6) {
				return binary_int{0};
			}
			binary = binary >> count;
		}
		count *= 2;
	}
	return binary;
}

binary_int binary_int::operator>>=(binary_int &rhs) {
	*this = *this >> rhs;
	return *this;
}

binary_int binary_int::operator<<=(binary_int &rhs) {
	*this = *this << rhs;
	return *this;
}

binary_int binary_int::operator>>=(int rhs) {
	*this = *this >> rhs;
	return *this;
}

binary_int binary_int::operator<<=(int rhs) {
	*this = *this << rhs;
	return *this;
}

binary_int binary_int::operator++() {
	binary_int tmp{1};
	*this = *this + tmp;
	return *this;
}

binary_int binary_int::operator++(int) {
	binary_int tmp{get_bit_representation()};
	binary_int tmp2{1};
	*this = *this + tmp2;
	return tmp;
}

binary_int binary_int::operator--() {
	binary_int tmp{1};
	*this = *this - tmp;
	return *this;
}

binary_int binary_int::operator--(int) {
	binary_int tmp{get_bit_representation()};
	binary_int tmp2{1};
	*this = *this - tmp2;
	return tmp;
}

binary_int binary_int::operator+=(binary_int &b) {
	*this = *this + b;
	return *this;
}

binary_int binary_int::operator-=(binary_int &b) {
	*this = *this - b;
	return *this;
}

binary_int binary_int::operator*=(binary_int &b) {
	*this = *this * b;
	return *this;
}
std::pair<binary_int, binary_int> binary_int::to_parts() {
	bool left[this->get_count_bits()];
	memset(left, false, get_count_bits());
	bool right[this->get_count_bits()];
	memset(right, false, get_count_bits());

	memmove(left, get_bit_representation(), get_count_bits() / 2);
	memmove(&(right[get_count_bits() / 2]), &(get_bit_representation()[get_count_bits() / 2]), get_count_bits() / 2);

	return {binary_int{left}, binary_int{right}};
}

std::ostream &operator<<(std::ostream &out, binary_int &binary) {
	if (binary.get_bit_representation()[0]) {
	}
	out << binary.get_bit_representation()[0] << " ";
	for (int i = 1; i < binary.get_count_bits(); i++) {
		out << binary.get_bit_representation()[i];
	}
	return out;
}
