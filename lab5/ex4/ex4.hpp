#pragma once

#include <cmath>
#include <iostream>


class Complex {
   protected:
	double real;
	double imaginary;

   public:
	explicit Complex(const double real = 0, const double imaginary = 0) : real(real), imaginary(imaginary){};
	Complex(const Complex& complex);
	Complex& operator=(const Complex& complex);

	double get_real() const;
	double get_imaginary() const;

	Complex operator+(const Complex& second) const;
	Complex& operator+=(const Complex& second) &;
	Complex operator-(const Complex& second) const;
	Complex& operator-=(const Complex& second) &;
	Complex operator*(const Complex& second) const;
	Complex& operator*=(const Complex& second) &;
	Complex operator/(const Complex& second) const;
	Complex& operator/=(const Complex& second) &;
	Complex operator-() const;

	double absolute() const;
	double argument() const;
};

std::ostream& operator<<(std::ostream& out, const Complex& complex);
