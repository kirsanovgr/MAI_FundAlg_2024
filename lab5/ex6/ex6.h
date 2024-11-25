
#ifndef LAB5_EX6_H
#define LAB5_EX6_H

#include <algorithm>
#include <cstring>
#include <initializer_list>
#include <iostream>
#include <iterator>

class incorrect_index : std::exception {};

class Vector {
   private:
	double* _data{};
	size_t _size{};
	size_t _capacity{};

   public:
	explicit Vector(size_t n = 0, double default_value = 0);

	Vector(const double *begin, const double *end);

	Vector(std::initializer_list<double> init);
	Vector(const Vector & vector);

	Vector& operator=(const Vector & vector);

	~Vector();

	size_t size() const;
	size_t capacity() const;
	void reserve(size_t num = 0);
	void shrink_to_fit();
	void clear();
	void insert(size_t index, double elem);
	void erase(size_t index);
	void push_back(double el);
	void pop_back();
	void resize(size_t size, double elem = 0);
	bool empty() const;

	double& at(size_t index);
	double& operator[](size_t index);
	double& front();
	double& back();
	double* data();

	const double& at(size_t index) const;
	const double& operator[](size_t index) const;
	const double& front() const;
	const double& back() const;
	const double* data() const;

	bool operator==(const Vector& other) const;
	std::weak_ordering operator<=>(const Vector& other) const;

	class Iterator {
	   private:
		double* ptr;

	   public:
		Iterator(double* prt) : ptr(prt){};

		double& operator*() const;
		double* operator->();
		Iterator& operator++()&;
		Iterator operator++(int);
		Iterator& operator--()&;
		Iterator operator--(int);
		Iterator operator+(size_t n) const;
		Iterator& operator+=(size_t n) &;
		Iterator& operator-=(size_t n) &;
		Iterator operator-(size_t n) const;
		size_t operator-(const Iterator& other) const;
		bool operator==(const Iterator& other) const;
		std::weak_ordering operator<=>(const Iterator& other) const;
		bool operator<(const Iterator& other) const;
		bool operator<=(const Iterator& other) const;
		bool operator>=(const Iterator& other) const;
		bool operator>(const Iterator& other) const;
		bool operator!=(const Iterator& other) const;
		double& operator[](size_t index);
		const double& operator[](size_t index) const;
	};

	Iterator begin();
	Iterator end();

	Iterator begin() const;
	Iterator end() const;
};


std::ostream& operator<<(std::ostream& ostream, const Vector& vector);

#endif  // LAB5_EX6_H
