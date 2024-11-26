#include <gtest/gtest.h>
#include "ex3.hpp"

TEST(LogicalValuesArrayTest, GetValue) {
	logical_values_array lva(0xFFFFFFFF);
	EXPECT_EQ(lva.get_value(), 0xFFFFFFFF);
}

TEST(LogicalValuesArrayTest, Equals) {
	logical_values_array lva1(0xFFFFFFFF);
	logical_values_array lva2(0xFFFFFFFF);
	logical_values_array lva3(0x00000000);
	EXPECT_TRUE(lva1.equals(lva1, lva2));
	EXPECT_FALSE(lva1.equals(lva1, lva3));
}

TEST(LogicalValuesArrayTest, ToCharArr) {
	logical_values_array lva(0x0000000F);
	char result[33];
	lva.to_char_arr(result);
	EXPECT_STREQ(result, "00000000000000000000000000001111");
}

TEST(LogicalValuesArrayTest, GetBit) {
	logical_values_array lva(0x0000000F);
	EXPECT_FALSE(lva.get_bit(0));
	EXPECT_FALSE(lva.get_bit(1));
	EXPECT_FALSE(lva.get_bit(2));
	EXPECT_FALSE(lva.get_bit(3));
	EXPECT_FALSE(lva.get_bit(4));
	EXPECT_TRUE(lva.get_bit(29));
	EXPECT_TRUE(lva.get_bit(30));
	EXPECT_TRUE(lva.get_bit(31));
	EXPECT_THROW(lva.get_bit(32), std::range_error);
}

TEST(LogicalValuesArrayTest, NotOperator) {
	logical_values_array lva(0x0000000F);
	logical_values_array result = ~lva;
	EXPECT_EQ(result.get_value(), 0xFFFFFFF0);
}

TEST(LogicalValuesArrayTest, AndOperator) {
	logical_values_array lva1(0x0000000F);
	logical_values_array lva2(0x000000F0);
	logical_values_array result = lva1 & lva2;
	EXPECT_EQ(result.get_value(), 0x00000000);
}

TEST(LogicalValuesArrayTest, OrOperator) {
	logical_values_array lva1(0x0000000F);
	logical_values_array lva2(0x000000F0);
	logical_values_array result = lva1 | lva2;
	EXPECT_EQ(result.get_value(), 0x000000FF);
}

TEST(LogicalValuesArrayTest, XorOperator) {
	logical_values_array lva1(0x0000000F);
	logical_values_array lva2(0x000000F0);
	logical_values_array result = lva1 ^ lva2;
	EXPECT_EQ(result.get_value(), 0x000000FF);
}

TEST(LogicalValuesArrayTest, LeqOperator) {
	logical_values_array lva1(0x0000000F);
	logical_values_array lva2(0x000000F0);
	logical_values_array result = lva1 <= lva2;
	EXPECT_EQ(result.get_value(), 0xFFFFFFF0);
}

TEST(LogicalValuesArrayTest, GtOperator) {
	logical_values_array lva1(0x0000000F);
	logical_values_array lva2(0x000000F0);
	logical_values_array result = lva1 > lva2;
	EXPECT_EQ(result.get_value(), 0x0000000F);
}

TEST(LogicalValuesArrayTest, EqOperator) {
	logical_values_array lva1(0x0000000F);
	logical_values_array lva2(0x0000000F);
	logical_values_array lva3(0x000000F0);
	logical_values_array result1 = lva1 == lva2;
	logical_values_array result2 = lva1 == lva3;
	EXPECT_EQ(result1.get_value(), 0xFFFFFFFF);
	EXPECT_EQ(result2.get_value(), 0xFFFFFF00);
}

TEST(LogicalValuesArrayTest, PierceArrow) {
	logical_values_array lva1(0x0000000F);
	logical_values_array lva2(0x000000F0);
	logical_values_array result = lva1.pierce_arrow(lva2);
	EXPECT_EQ(result.get_value(), 0xFFFFFF00);
}

TEST(LogicalValuesArrayTest, ShefferStroke) {
	logical_values_array lva1(0x0000000F);
	logical_values_array lva2(0x000000F0);
	logical_values_array result = lva1.sheffer_stroke(lva2);
	EXPECT_EQ(result.get_value(), 0xFFFFFFFF);
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}