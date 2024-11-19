
#include "ex4.h"
Complex Complex::operator+(const Complex& second) const {
	return Complex{real + second.get_real(), imaginary + second.get_imaginary()};
}
Complex Complex::operator-(const Complex& second) const {
	return Complex{real - second.get_real(), imaginary - second.get_imaginary()};
}
Complex Complex::operator*(const Complex& second) const {
	return Complex{real * second.get_real() - imaginary * second.get_imaginary(),
	               imaginary * second.get_real() + real * second.get_imaginary()};
}

Complex Complex::operator/(const Complex& second) const {
	if(std::fabs(second.absolute()) < 1e-20){
		throw div_by_null();
	}
	return Complex{(real * second.get_real() + imaginary * second.get_imaginary()) / (second.get_real() * second.get_real() + second.get_imaginary() * second.get_imaginary()),
		(imaginary * second.get_real() - real * second.get_imaginary()) / (second.get_real() * second.get_real() + second.get_imaginary() * second.get_imaginary())};
}

double Complex::get_real() const { return real; }
double Complex::get_imaginary() const { return imaginary; }
Complex Complex::operator+=(const Complex& second) {
    *this = *this + second;
	return *this;
}
Complex Complex::operator-=(const Complex& second) {
	*this = *this - second;
	return *this;
}
Complex Complex::operator*=(const Complex& second) {
	*this = *this * second;
	return *this;
}
Complex Complex::operator/=(const Complex& second) {
    *this = *this / second;
	return *this;
}
Complex Complex::operator-() const {
    return Complex{-real, -imaginary};
}
double Complex::absolute() const {
    return std::sqrt(real * real + imaginary * imaginary);
}
double Complex::argument() const {
    return std::atan2(imaginary, real);
}

std::ostream& operator<<(std::ostream& out, const Complex& complex) {
	out << complex.get_real() << " " << complex.get_imaginary() << "i" << std::endl;
	return out;
}

