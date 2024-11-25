#include <iostream>
#include <cmath>
#include <stdexcept>
#include <iomanip>

class ComplexNumber {
private:
    double real;
    double imag;

public:
    ComplexNumber(double r = 0.0, double i = 0.0) : real(r), imag(i) {}

    ComplexNumber(const ComplexNumber& other) : real(other.real), imag(other.imag) {}

    ComplexNumber& operator=(const ComplexNumber& other) {
        if (this != &other) {
            real = other.real;
            imag = other.imag;
        }
        return *this;
    }

    ~ComplexNumber() {}

    ComplexNumber operator+(const ComplexNumber& other) const {
        return ComplexNumber(real + other.real, imag + other.imag);
    }

    ComplexNumber operator-(const ComplexNumber& other) const {
        return ComplexNumber(real - other.real, imag - other.imag);
    }

    ComplexNumber operator*(const ComplexNumber& other) const {
        double r = real * other.real - imag * other.imag;
        double i = real * other.imag + imag * other.real;
        return ComplexNumber(r, i);
    }

    ComplexNumber operator/(const ComplexNumber& other) const {
        double denominator = other.real * other.real + other.imag * other.imag;
        if (denominator == 0) {
            throw std::invalid_argument("Division by zero is not possible");
        }
        double r = (real * other.real + imag * other.imag) / denominator;
        double i = (imag * other.real - real * other.imag) / denominator;
        return ComplexNumber(r, i);
    }

    double modulus() const {
        return std::sqrt(real * real + imag * imag);
    }

    double argument() const {
        return std::atan2(imag, real);
    }

    void print() const {
        std::cout << std::fixed << std::setprecision(2);
        std::cout << real << (imag >= 0 ? " + " : " - ") << std::fabs(imag) << "i" << std::endl;
    }

    double getReal() const { return real; }
    double getImag() const { return imag; }
};

int main() {
    try {
        // пример комплексных чисел:
        ComplexNumber c1(3.0, 4.0); // 3 + 4i
        ComplexNumber c2(1.0, -2.0); // 1 - 2i

        std::cout << "Complex number 1: ";
        c1.print();
        std::cout << "Complex number 2: ";
        c2.print();

        ComplexNumber sum = c1 + c2;
        ComplexNumber diff = c1 - c2;
        ComplexNumber prod = c1 * c2;
        ComplexNumber div = c1 / c2;

        std::cout << "Sum: ";
        sum.print();
        std::cout << "Difference: ";
        diff.print();
        std::cout << "Product: ";
        prod.print();
        std::cout << "Quotient: ";
        div.print();

        std::cout << "Modulus of the first number: " << c1.modulus() << std::endl;
        std::cout << "Argument of the first number: " << c1.argument() << " radians" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}