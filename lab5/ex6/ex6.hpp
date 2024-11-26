#pragma once

#include <algorithm>
#include <cstring>
#include <initializer_list>
#include <iostream>
#include <iterator>


class Vector {
   private:
	double* _data{};
	size_t _size{};
	size_t _capacity{};

   public:
	explicit Vector(size_t n = 0, double default_value = 0);

	class Iterator;

	template <class InputIt>
	Vector(InputIt begin, InputIt end, typename InputIt::iterator_category *p = 0);

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

	Iterator begin();
	Iterator end();

	Iterator cbegin() const;
	Iterator cend() const;
};

std::ostream& operator<<(std::ostream& ostream, const Vector& vector);


class Vector::Iterator {
   private:
	double* ptr;

   public:
	using iterator_category = std::random_access_iterator_tag;
	using value_type = double;
	using difference_type = std::ptrdiff_t;
	using pointer = double*;
	using reference = double&;

	explicit Iterator(pointer prt) : ptr(prt){};

	reference operator*() const;
	pointer operator->();
	Iterator& operator++();
	Iterator operator++(int);
	Iterator& operator--()&;
	Iterator operator--(int);
	Iterator operator+(difference_type n) const;
	Iterator& operator+=(difference_type n) &;
	Iterator& operator-=(difference_type n) &;
	Iterator operator-(difference_type n) const;
	difference_type operator-(const Iterator& other) const;
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

template <class InputIt>
Vector::Vector(InputIt begin, InputIt end, InputIt::iterator_category *p)  {
	_size = end - begin;
	_capacity = _size;
	_data = new double [_size];
	std::copy(begin, end, _data);
}

