#pragma once
#include <cstddef>   // size_t
#include <stdexcept> // std::out_of_range
#include <cstring>   // memcpy, memset

class vector {
private:
	size_t _size;       // Текущее количество элементов
	size_t _capacity;   // Вместимость массива
	double* _data;      // Указатель на массив данных

	void reallocate(size_t new_capacity);

public:
	// Конструкторы
	vector();
	explicit vector(size_t count, double value = 0.0);
	explicit vector(size_t count);
	vector(const vector& other);
	vector& operator=(const vector& other);
	~vector();

	// Методы доступа
	double& at(size_t index);
	const double& at(size_t index) const;

	double& front();
	const double& front() const;

	double& back();
	const double& back() const;

	double* data();
	const double* data() const;

	// Информация о векторе
	bool empty() const;
	size_t size() const;
	size_t capacity() const;

	// Управление памятью
	void reserve(size_t num);
	void shrink_to_fit();
	void clear();

	// Модификация вектора
	void insert(size_t index, double elem);
	void erase(size_t index);
	void push_back(double elem);
	void pop_back();
	void resize(size_t new_size, double elem = 0.0);

	// Операторы
	bool operator==(const vector& other) const;
	bool operator!=(const vector& other) const;
	bool operator<(const vector& other) const;
	bool operator<=(const vector& other) const;
	bool operator>(const vector& other) const;
	bool operator>=(const vector& other) const;

	// Итераторы
	using iterator = double*;
	using const_iterator = const double*;

	iterator begin();
	iterator end();
	const_iterator cbegin() const;
	const_iterator cend() const;
};
