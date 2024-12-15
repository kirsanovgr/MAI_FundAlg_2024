#pragma once

#include <cstring>
#include <iostream>
#include <memory>
#include <vector>
class binary_int {
   private:

	int number;
	static int add(int a, int b);
	static int sub(int a, int b);

   public:
	binary_int();
	binary_int(int a);
	int get_number() const;
	binary_int operator-() const;
	binary_int operator+(binary_int x) const;
	binary_int operator-(binary_int x) const;
	binary_int &operator+=(binary_int x);
	binary_int &operator-=(binary_int x);
	binary_int &operator++()&;
	binary_int &operator--()&;
	binary_int operator++(int);
	binary_int operator--(int);
	bool operator<(binary_int x) const;
	binary_int &operator*=(binary_int x);
	binary_int operator*(binary_int x) const;
	binary_int operator<<(binary_int x) const;
	binary_int operator>>(binary_int x) const;
	binary_int &operator<<=(binary_int x);
	binary_int &operator>>=(binary_int x);
	binary_int operator&(binary_int) const;

	std::pair<binary_int, binary_int> to_parts() const;
};

std::ostream &operator<<(std::ostream &stream, binary_int binaryInt);
