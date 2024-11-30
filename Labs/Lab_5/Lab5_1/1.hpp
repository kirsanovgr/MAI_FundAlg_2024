#pragma once

#include <iostream>
#include <utility>

class binary_int {
private:
	int value;

public:
	explicit binary_int(int v);
	binary_int() = default;

	binary_int operator-() const;

	binary_int &operator++();

	binary_int operator++(int);

	binary_int &operator--();

	binary_int operator--(int);

	binary_int &operator+=(const binary_int &other);
	binary_int operator+(const binary_int &other) const;
	binary_int &operator-=(const binary_int &other);
	binary_int operator-(const binary_int &other) const;

	binary_int &operator*=(const binary_int &other);
	binary_int operator*(const binary_int &other) const;

	binary_int &operator<<=(int shift);
	binary_int operator<<(int shift) const;
	binary_int &operator>>=(int shift);
	binary_int operator>>(int shift) const;

	// Метод получения двух частей битов
	std::pair<binary_int, binary_int> split_bits() const;

	// для вставки в поток
	friend std::ostream &operator<<(std::ostream &os, const binary_int &obj);

private:
	static int add(int a, int b);
	static int multiply(int a, int b);
};
