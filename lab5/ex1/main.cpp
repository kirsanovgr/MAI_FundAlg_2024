#include <iostream>

#include "ex1.hpp"

void test_addition() {
	std::cout << "Testing addition:" << std::endl;
	binary_int a(10);  // 10 в десятичной
	binary_int b(5);   // 5 в десятичной
	binary_int sum = a + b;
	std::cout << "10 + 5: " << sum << std::endl;

	binary_int c(-10); // -10 в десятичной
	binary_int d(5);   // 5 в десятичной
	binary_int sum2 = c + d;
	std::cout << "-10 + 5: " << sum2 << std::endl;

	binary_int e(10);  // 10 в десятичной
	binary_int f(-5);  // -5 в десятичной
	binary_int sum3 = e + f;
	std::cout << "10 + (-5): " << sum3 << std::endl;

	binary_int g(-10); // -10 в десятичной
	binary_int h(-5);  // -5 в десятичной
	binary_int sum4 = g + h;
	std::cout << "-10 + (-5): " << sum4 << std::endl;
}

void test_subtraction() {
	std::cout << "Testing subtraction:" << std::endl;
	binary_int a(10);  // 10 в десятичной
	binary_int b(5);   // 5 в десятичной
	binary_int diff = a - b;
	std::cout << "10 - 5: " << diff << std::endl;

	binary_int c(-10); // -10 в десятичной
	binary_int d(5);   // 5 в десятичной
	binary_int diff2 = c - d;
	std::cout << "-10 - 5: " << diff2 << std::endl;

	binary_int e(10);  // 10 в десятичной
	binary_int f(-5);  // -5 в десятичной
	binary_int diff3 = e - f;
	std::cout << "10 - (-5): " << diff3 << std::endl;

	binary_int g(-10); // -10 в десятичной
	binary_int h(-5);  // -5 в десятичной
	binary_int diff4 = g - h;
	std::cout << "-10 - (-5): " << diff4 << std::endl;
}

void test_multiplication() {
	std::cout << "Testing multiplication:" << std::endl;
	binary_int a(10);  // 10 в десятичной
	binary_int b(5);   // 5 в десятичной
	binary_int prod = a * b;
	std::cout << "10 * 5: " << prod << std::endl;

	binary_int c(-10); // -10 в десятичной
	binary_int d(5);   // 5 в десятичной
	binary_int prod2 = c * d;
	std::cout << "-10 * 5: " << prod2 << std::endl;

	binary_int e(10);  // 10 в десятичной
	binary_int f(-5);  // -5 в десятичной
	binary_int prod3 = e * f;
	std::cout << "10 * (-5): " << prod3 << std::endl;


	binary_int g(-10); // -10 в десятичной
	binary_int h(-5);  // -5 в десятичной
	binary_int prod4 = g * h;
	std::cout << "-10 * (-5): " << prod4 << std::endl;
}

void test_shift_operations() {
	std::cout << "Testing shift operations:" << std::endl;
	binary_int a(10);  // 10 в десятичной
	binary_int shift_left = a << 2;
	std::cout << "10 << 2: " << shift_left << std::endl;

	binary_int shift_right = a >> 2;
	std::cout << "10 >> 2: " << shift_right << std::endl;

	binary_int b(-10); // -10 в десятичной
	binary_int shift_left2 = b << 2;
	std::cout << "-10 << 2: " << shift_left2 << std::endl;

	binary_int shift_right2 = b >> 2;
	std::cout << "-10 >> 2: " << shift_right2 << std::endl;
}

void test_increment_decrement() {
	std::cout << "Testing increment and decrement:" << std::endl;
	binary_int a(10);  // 10 в десятичной
	binary_int inc = a++;
	std::cout << "a++: " << inc << std::endl;

	inc = ++(--a);
	std::cout << "++a: " << inc << std::endl;

	binary_int dec = a--;
	std::cout << "a--: " << dec << std::endl;

	dec = --(++a);
	std::cout << "--a: " << dec << std::endl;

	binary_int b(-10); // -10 в десятичной
	binary_int inc2 = b++;
	std::cout << "b++: " << inc2 << std::endl;

	binary_int dec2 = b--;
	std::cout << "b--: " << dec2 << std::endl;
}


void test_to_part(){
	binary_int a{-1};
	std::pair<binary_int, binary_int> pair;
	pair = a.to_parts();
	std::cout << "first_el: " << pair.first << std::endl;
	std::cout << "second_el:" << pair.second << std::endl;
}

int main() {
	test_addition();
	test_subtraction();
	test_multiplication();
	test_shift_operations();
	test_increment_decrement();
	test_to_part();

	return 0;
}