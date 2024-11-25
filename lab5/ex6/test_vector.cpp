#include "ex6.h"
#include <gtest/gtest.h>
#include <stdexcept>

// Тесты для конструкторов
TEST(VectorTest, DefaultConstructor) {
	Vector v;
	EXPECT_EQ(v.size(), 0);
	EXPECT_EQ(v.capacity(), 0);
}

TEST(VectorTest, SizeConstructor) {
	Vector v(5);
	EXPECT_EQ(v.size(), 5);
	EXPECT_EQ(v.capacity(), 5);
	for (size_t i = 0; i < v.size(); ++i) {
		EXPECT_EQ(v[i], 0.0);
	}
}

TEST(VectorTest, SizeValueConstructor) {
	Vector v(5, 1.0);
	EXPECT_EQ(v.size(), 5);
	EXPECT_EQ(v.capacity(), 5);
	for (size_t i = 0; i < v.size(); ++i) {
		EXPECT_EQ(v[i], 1.0);
	}
}

TEST(VectorTest, IteratorConstructor) {
	std::vector<double> init = {1.0, 2.0, 3.0};
	Vector v(init.begin(), init.end());
	EXPECT_EQ(v.size(), 3);
	EXPECT_EQ(v.size(), 3);
	EXPECT_EQ(v.capacity(), 3);
	for (size_t i = 0; i < v.size(); ++i) {
		EXPECT_EQ(v[i], init[i]);
	}
}

TEST(VectorTest, InitializerListConstructor) {
	Vector v = {1.0, 2.0, 3.0};
	EXPECT_EQ(v.size(), 3);
	EXPECT_EQ(v.capacity(), 3);
	for (size_t i = 0; i < v.size(); ++i) {
		EXPECT_EQ(v[i], i + 1.0);
	}
}

// Тесты для метода at
TEST(VectorTest, At) {
	Vector v = {1.0, 2.0, 3.0};
	EXPECT_EQ(v.at(0), 1.0);
	EXPECT_EQ(v.at(1), 2.0);
	EXPECT_EQ(v.at(2), 3.0);
	EXPECT_THROW(v.at(3), incorrect_index);
}

TEST(VectorTest, AtConst) {
	const Vector v = {1.0, 2.0, 3.0};
	EXPECT_EQ(v.at(0), 1.0);
	EXPECT_EQ(v.at(1), 2.0);
	EXPECT_EQ(v.at(2), 3.0);
	EXPECT_THROW(v.at(3), incorrect_index);
}

// Тесты для метода front
TEST(VectorTest, Front) {
	Vector v = {1.0, 2.0, 3.0};
	EXPECT_EQ(v.front(), 1.0);
	v.front() = 4.0;
	EXPECT_EQ(v.front(), 4.0);
}

TEST(VectorTest, FrontConst) {
	const Vector v = {1.0, 2.0, 3.0};
	EXPECT_EQ(v.front(), 1.0);
}

// Тесты для метода back
TEST(VectorTest, Back) {
	Vector v = {1.0, 2.0, 3.0};
	EXPECT_EQ(v.back(), 3.0);
	v.back() = 4.0;
	EXPECT_EQ(v.back(), 4.0);
}

TEST(VectorTest, BackConst) {
	const Vector v = {1.0, 2.0, 3.0};
	EXPECT_EQ(v.back(), 3.0);
}

// Тесты для метода data
TEST(VectorTest, Data) {
	Vector v = {1.0, 2.0, 3.0};
	double* data = v.data();
	for (size_t i = 0; i < v.size(); ++i) {
		EXPECT_EQ(data[i], i + 1.0);
	}
}

TEST(VectorTest, DataConst) {
	const Vector v = {1.0, 2.0, 3.0};
	const double* data = v.data();
	for (size_t i = 0; i < v.size(); ++i) {
		EXPECT_EQ(data[i], i + 1.0);
	}
}

// Тесты для метода empty
TEST(VectorTest, Empty) {
	Vector v;
	EXPECT_TRUE(v.empty());
	v.push_back(1.0);
	EXPECT_FALSE(v.empty());
}

TEST(VectorTest, EmptyConst) {
	const Vector v;
	EXPECT_TRUE(v.empty());
}

// Тесты для метода size
TEST(VectorTest, Size) {
	Vector v = {1.0, 2.0, 3.0};
	EXPECT_EQ(v.size(), 3);
	v.push_back(4.0);
	EXPECT_EQ(v.size(), 4);
}

TEST(VectorTest, SizeConst) {
	const Vector v = {1.0, 2.0, 3.0};
	EXPECT_EQ(v.size(), 3);
}

// Тесты для метода reserve
TEST(VectorTest, Reserve) {
	Vector v;
	v.reserve(10);
	EXPECT_GE(v.capacity(), 10);
}

// Тесты для метода capacity
TEST(VectorTest, Capacity) {
	Vector v;
	EXPECT_EQ(v.capacity(), 0);
	v.reserve(10);
	EXPECT_GE(v.capacity(), 10);
}

TEST(VectorTest, CapacityConst) {
	const Vector v;
	EXPECT_EQ(v.capacity(), 0);
}

// Тесты для метода shrink_to_fit
TEST(VectorTest, ShrinkToFit) {
	Vector v = {1.0, 2.0, 3.0};
	v.reserve(10);
	EXPECT_GE(v.capacity(), 10);
	v.shrink_to_fit();
	EXPECT_EQ(v.capacity(), v.size());
}


// Тесты для метода clear
TEST(VectorTest, Clear) {
	Vector v = {1.0, 2.0, 3.0};
	v.clear();
	EXPECT_EQ(v.size(), 0);
	EXPECT_GE(v.capacity(), 3);
}


// Тесты для метода insert
TEST(VectorTest, Insert) {
	Vector v = {1.0, 2.0, 3.0};
	v.insert(1, 4.0);
	EXPECT_EQ(v.size(), 4);
	EXPECT_EQ(v[0], 1.0);
	EXPECT_EQ(v[1], 4.0);
	EXPECT_EQ(v[2], 2.0);
	EXPECT_EQ(v[3], 3.0);
}


// Тесты для метода erase
TEST(VectorTest, Erase) {
	Vector v = {1.0, 2.0, 3.0};
	v.erase(1);
	EXPECT_EQ(v.size(), 2);
	EXPECT_EQ(v[0], 1.0);
	EXPECT_EQ(v[1], 3.0);
}
// Тесты для метода push_back
TEST(VectorTest, PushBack) {
	Vector v;
	v.push_back(1.0);
	v.push_back(2.0);
	v.push_back(3.0);
	EXPECT_EQ(v.size(), 3);
	for (size_t i = 0; i < v.size(); ++i) {
		EXPECT_EQ(v[i], i + 1.0);
	}
}

// Тесты для метода pop_back
TEST(VectorTest, PopBack) {
	Vector v = {1.0, 2.0, 3.0};
	v.pop_back();
	EXPECT_EQ(v.size(), 2);
	EXPECT_EQ(v[0], 1.0);
	EXPECT_EQ(v[1], 2.0);
}


// Тесты для метода resize
TEST(VectorTest, Resize) {
	Vector v = {1.0, 2.0, 3.0};
	v.resize(5, 4.0);
	EXPECT_EQ(v.size(), 5);
	EXPECT_EQ(v[0], 1.0);
	EXPECT_EQ(v[1], 2.0);
	EXPECT_EQ(v[2], 3.0);
	EXPECT_EQ(v[3], 4.0);
	EXPECT_EQ(v[4], 4.0);
}

// Тесты для операторов сравнения
TEST(VectorTest, ComparisonOperators) {
	Vector v1 = {1.0, 2.0, 3.0};
	Vector v2 = {1.0, 2.0, 3.0};
	Vector v3 = {1.0, 2.0, 4.0};
	Vector v4 = {1.0, 2.0};

	EXPECT_TRUE(v1 == v2);
	EXPECT_FALSE(v1 == v3);
	EXPECT_FALSE(v1 == v4);

	EXPECT_TRUE(v1 != v3);
	EXPECT_TRUE(v1 != v4);

	EXPECT_TRUE(v1 < v3);
	EXPECT_FALSE(v3 < v1);

	EXPECT_TRUE(v1 <= v2);
	EXPECT_TRUE(v1 <= v3);

	EXPECT_TRUE(v3 > v1);
	EXPECT_FALSE(v1 > v3);

	EXPECT_TRUE(v2 >= v1);
	EXPECT_TRUE(v3 >= v1);
}

TEST(VectorTest, ComparisonOperatorsConst) {
	const Vector v1 = {1.0, 2.0, 3.0};
	const Vector v2 = {1.0, 2.0, 3.0};
	const Vector v3 = {1.0, 2.0, 4.0};
	const Vector v4 = {1.0, 2.0};

	EXPECT_TRUE(v1 == v2);
	EXPECT_FALSE(v1 == v3);
	EXPECT_FALSE(v1 == v4);

	EXPECT_TRUE(v1 != v3);
	EXPECT_TRUE(v1 != v4);

	EXPECT_TRUE(v1 < v3);
	EXPECT_FALSE(v3 < v1);

	EXPECT_TRUE(v1 <= v2);
	EXPECT_TRUE(v1 <= v3);

	EXPECT_TRUE(v3 > v1);
	EXPECT_FALSE(v1 > v3);

	EXPECT_TRUE(v2 >= v1);
	EXPECT_TRUE(v3 >= v1);
}

// Тесты для итераторов
TEST(VectorTest, Iterators) {
	Vector v = {1.0, 2.0, 3.0};
	size_t i = 0;
	for (auto it = v.begin(); it != v.end(); ++it) {
		EXPECT_EQ(*it, v[i++]);
	}
}

TEST(VectorTest, IteratorsConst) {
	const Vector v = {1.0, 2.0, 3.0};
	size_t i = 0;
	for (auto it = v.begin(); it != v.end(); ++it) {
		EXPECT_EQ(*it, v[i++]);
	}
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}