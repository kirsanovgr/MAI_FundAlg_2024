#ifndef LAB5_EX1_H
#define LAB5_EX1_H

#include <cstring>
#include <iostream>
#include <memory>
#include <vector>

int add(int a, int b);
int sub(int a, int b);

class binary_int {
   protected:
	bool bit_representation[32];

	// конструктор получающий массив bool
	binary_int(const bool *number);

   private:
	int count_bits;
	void to_reserve_code();

   public:
	binary_int(int number = 0);

	bool *get_bit_representation();
	int get_count_bits() const;

	binary_int operator-();
	binary_int operator+(binary_int &b);
	binary_int operator+=(binary_int &b);
	binary_int operator-(binary_int &b);
	binary_int operator-=(binary_int &b);
	binary_int operator*(binary_int &b);
	binary_int operator*=(binary_int &b);
	binary_int operator++();
	binary_int operator++(int);
	binary_int operator--();
	binary_int operator--(int);

	binary_int operator<<(int shift);
	binary_int operator>>(int shift);
	binary_int operator<<(binary_int &rhs);
	binary_int operator>>(binary_int &rhs);
	binary_int operator>>=(binary_int &rhs);
	binary_int operator<<=(binary_int &rhs);
	binary_int operator>>=(int rhs);
	binary_int operator<<=(int rhs);

	std::pair<binary_int, binary_int> to_parts();
};

std::ostream &operator<<(std::ostream &out, binary_int &binary);

#endif  // LAB5_EX1_H
