#include <gtest/gtest.h>
#include "ex4.hpp"

TEST(ComplexTest, Addition) {
	Complex a(1.0, 2.0);
	Complex b(3.0, 4.0);
	Complex result = a + b;
	EXPECT_DOUBLE_EQ(result.get_real(), 4.0);
	EXPECT_DOUBLE_EQ(result.get_imaginary(), 6.0);
}

TEST(ComplexTest, Subtraction) {
	Complex a(5.0, 3.0);
	Complex b(2.0, 1.0);
	Complex result = a - b;
	EXPECT_DOUBLE_EQ(result.get_real(), 3.0);
	EXPECT_DOUBLE_EQ(result.get_imaginary(), 2.0);
}

TEST(ComplexTest, Multiplication) {
	Complex a(1.0, 2.0);
	Complex b(3.0, 4.0);
	Complex result = a * b;
	EXPECT_DOUBLE_EQ(result.get_real(), -5.0);
	EXPECT_DOUBLE_EQ(result.get_imaginary(), 10.0);
}

TEST(ComplexTest, Division) {
	Complex a(1.0, 2.0);
	Complex b(3.0, 4.0);
	Complex result = a / b;
	EXPECT_DOUBLE_EQ(result.get_real(), 0.44);
	EXPECT_DOUBLE_EQ(result.get_imaginary(), 0.08);
}

TEST(ComplexTest, DivisionByZero) {
	Complex a(1.0, 2.0);
	Complex b(0.0, 0.0);
	EXPECT_THROW(a / b, std::invalid_argument);
}

TEST(ComplexTest, AdditionAssignment) {
	Complex a(1.0, 2.0);
	Complex b(3.0, 4.0);
	a += b;
	EXPECT_DOUBLE_EQ(a.get_real(), 4.0);
	EXPECT_DOUBLE_EQ(a.get_imaginary(), 6.0);
}

TEST(ComplexTest, SubtractionAssignment) {
	Complex a(5.0, 3.0);
	Complex b(2.0, 1.0);
	a -= b;
	EXPECT_DOUBLE_EQ(a.get_real(), 3.0);
	EXPECT_DOUBLE_EQ(a.get_imaginary(), 2.0);
}

TEST(ComplexTest, MultiplicationAssignment) {
	Complex a(1.0, 2.0);
	Complex b(3.0, 4.0);
	a *= b;
	EXPECT_DOUBLE_EQ(a.get_real(), -5.0);
	EXPECT_DOUBLE_EQ(a.get_imaginary(), 10.0);
}

TEST(ComplexTest, DivisionAssignment) {
	Complex a(1.0, 2.0);
	Complex b(3.0, 4.0);
	a /= b;
	EXPECT_DOUBLE_EQ(a.get_real(), 0.44);
	EXPECT_DOUBLE_EQ(a.get_imaginary(), 0.08);
}

TEST(ComplexTest, UnaryMinus) {
	Complex a(1.0, 2.0);
	Complex result = -a;
	EXPECT_DOUBLE_EQ(result.get_real(), -1.0);
	EXPECT_DOUBLE_EQ(result.get_imaginary(), -2.0);
}

TEST(ComplexTest, Absolute) {
	Complex a(3.0, 4.0);
	double result = a.absolute();
	EXPECT_DOUBLE_EQ(result, 5.0);
}

TEST(ComplexTest, Argument) {
	Complex a(1.0, 1.0);
	double result = a.argument();
	EXPECT_DOUBLE_EQ(result, M_PI / 4);
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}