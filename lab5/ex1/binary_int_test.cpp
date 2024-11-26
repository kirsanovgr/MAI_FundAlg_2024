#include <gtest/gtest.h>
#include "ex1.hpp"

// Тестовый случай для конструктора по умолчанию
TEST(BinaryIntTest, DefaultConstructor) {
	binary_int b;
	EXPECT_EQ(b.get_number(), 0);
}

// Тестовый случай для конструктора с параметром
TEST(BinaryIntTest, ParameterizedConstructor) {
	binary_int b(42);
	EXPECT_EQ(b.get_number(), 42);
}

// Тестовый случай для оператора унарного минуса
TEST(BinaryIntTest, UnaryMinus) {
	binary_int b(42);
	binary_int neg_b = -b;
	EXPECT_EQ(neg_b.get_number(), -42);
}

// Тестовый случай для оператора сложения
TEST(BinaryIntTest, Addition) {
	binary_int b1(20);
	binary_int b2(22);
	binary_int sum = b1 + b2;
	EXPECT_EQ(sum.get_number(), 42);
}

// Тестовый случай для оператора вычитания
TEST(BinaryIntTest, Subtraction) {
	binary_int b1(50);
	binary_int b2(8);
	binary_int diff = b1 - b2;
	EXPECT_EQ(diff.get_number(), 42);
}

// Тестовый случай для оператора присваивания сложения
TEST(BinaryIntTest, AdditionAssignment) {
	binary_int b1(20);
	binary_int b2(22);
	b1 += b2;
	EXPECT_EQ(b1.get_number(), 42);
}

// Тестовый случай для оператора присваивания вычитания
TEST(BinaryIntTest, SubtractionAssignment) {
	binary_int b1(50);
	binary_int b2(8);
	b1 -= b2;
	EXPECT_EQ(b1.get_number(), 42);
}

// Тестовый случай для оператора присваивания умножения
TEST(BinaryIntTest, MultiplicationAssignment) {
	binary_int b1(6);
	binary_int b2(7);
	b1 *= b2;
	EXPECT_EQ(b1.get_number(), 42);
}

// Тестовый случай для префиксного инкремента
TEST(BinaryIntTest, PrefixIncrement) {
	binary_int b(41);
	++b;
	EXPECT_EQ(b.get_number(), 42);
}

// Тестовый случай для префиксного декремента
TEST(BinaryIntTest, PrefixDecrement) {
	binary_int b(43);
	--b;
	EXPECT_EQ(b.get_number(), 42);
}

// Тестовый случай для оператора сравнения "меньше"
TEST(BinaryIntTest, LessThan) {
	binary_int b1(41);
	binary_int b2(42);
	EXPECT_TRUE(b1 < b2);
	EXPECT_FALSE(b2 < b1);
}

// Тестовый случай для оператора умножения
TEST(BinaryIntTest, Multiplication) {
	binary_int b1(6);
	binary_int b2(7);
	binary_int product = b1 * b2;
	EXPECT_EQ(product.get_number(), 42);
}

// Тестовый случай для оператора сдвига влево
TEST(BinaryIntTest, LeftShift) {
	binary_int b(2);
	binary_int shift(3);
	binary_int result = b << shift;
	EXPECT_EQ(result.get_number(), 16);
}

// Тестовый случай для оператора сдвига вправо
TEST(BinaryIntTest, RightShift) {
	binary_int b(16);
	binary_int shift(3);
	binary_int result = b >> shift;
	EXPECT_EQ(result.get_number(), 2);
}

// Тестовый случай для оператора побитового И
TEST(BinaryIntTest, BitwiseAnd) {
	binary_int b1(6);  // 0110
	binary_int b2(3);  // 0011
	binary_int result = b1 & b2;
	EXPECT_EQ(result.get_number(), 2);  // 0010
}

// Тестовый случай для метода to_parts
TEST(BinaryIntTest, ToParts) {
	binary_int b(0x12345678);
	auto parts = b.to_parts();
	EXPECT_EQ(parts.first.get_number(), 0x12340000);
	EXPECT_EQ(parts.second.get_number(), 0x00005678);
}

// Тестовый случай для постфиксного инкремента
TEST(BinaryIntTest, PostfixIncrement) {
	binary_int b(41);
	binary_int result = b++;
	EXPECT_EQ(result.get_number(), 41);
	EXPECT_EQ(b.get_number(), 42);
}

// Тестовый случай для постфиксного декремента
TEST(BinaryIntTest, PostfixDecrement) {
	binary_int b(43);
	binary_int result = b--;
	EXPECT_EQ(result.get_number(), 43);
	EXPECT_EQ(b.get_number(), 42);
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}