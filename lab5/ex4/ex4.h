#ifndef LAB5_EX4_H
#define LAB5_EX4_H

#include <cmath>
#include <iostream>

class div_by_null : std::exception {};

class Complex {
   protected:
	double real;
	double imaginary;

   public:
	Complex(const double real = 0, const double imaginary = 0) : real(real), imaginary(imaginary){};

	double get_real() const;
	double get_imaginary() const;

	Complex operator+(const Complex& second) const;
	Complex& operator+=(const Complex& second);
	Complex operator-(const Complex& second) const;
	Complex& operator-=(const Complex& second);
	Complex operator*(const Complex& second) const;
	Complex& operator*=(const Complex& second);
	Complex operator/(const Complex& second) const;
	Complex& operator/=(const Complex& second);
	Complex operator-() const;

	double absolute() const;
	double argument() const;
};

std::ostream& operator<<(std::ostream& out, const Complex& complex);

#endif  // LAB5_EX4_H
