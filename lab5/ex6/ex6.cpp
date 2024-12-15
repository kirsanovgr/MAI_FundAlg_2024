

#include "ex6.hpp"
Vector::Vector(const size_t n, const double default_value) : _size(n), _capacity(n){
	_data = new double[n];
	for (size_t i = 0; i < n; ++i) {
		_data[i] = default_value;
	}
}
Vector::~Vector() {
	_capacity = 0;
	_size = 0;
	delete[] _data;
}
size_t Vector::size() const { return _size; }
size_t Vector::capacity() const { return _capacity; }
double &Vector::operator[](size_t index) { return _data[index]; }
const double &Vector::operator[](size_t index) const { return _data[index]; }
double &Vector::at(size_t index) {
	if (index >= _size) {
		throw std::range_error("Incorrect index");
	}
	return _data[index];
}
const double &Vector::at(size_t index) const {
	if (index >= _size) {
		throw std::range_error("Incorrect index");
	}
	return _data[index];
}
double &Vector::front() { return _data[0]; }
const double &Vector::front() const { return _data[0]; }

double &Vector::back() { return _data[_size - 1]; }
const double &Vector::back() const { return _data[_size - 1]; }
double *Vector::data() { return _data; }
const double *Vector::data() const { return _data; }
void Vector::reserve(size_t num) {
	if (num <= capacity()) {
		return;
	}
	double *new_arr = new double[num];
	std::memset(new_arr, 0, num * sizeof(double));
	std::memcpy(new_arr, _data, _size * sizeof(double));
	delete[] _data;
	_data = new_arr;
	_capacity = num;
}
void Vector::shrink_to_fit() {
	if (_size == capacity()) {
		return;
	}
	double *new_arr = new double[_size];
	std::memmove(new_arr, _data, _size * sizeof(double));
	delete[] _data;
	_data = new_arr;
	_capacity = _size;
}
void Vector::clear() { _size = 0; }
void Vector::insert(size_t index, double elem) {
	if (index >= capacity() + 1) {
		reserve(index + 10);
		_size = index + 1;
	} else {
		reserve(_capacity + 10);
		_size += 1;
	}
	for (size_t i = _size - 1; i > index; --i) {
		_data[i] = _data[i - 1];
	}
	_data[index] = elem;
}
void Vector::erase(size_t index) {
	if (index >= _size) {
		throw std::range_error("Incorrect index");
	}

	for (size_t i = index + 1; i < _size; ++i) {
		_data[i - 1] = _data[i];
	}
	_size--;
}
void Vector::push_back(double el) { insert(_size, el); }
void Vector::pop_back() {
	if (_size == 0) {
		throw std::range_error("Incorrect index");
	}
	_size -= 1;
}
void Vector::resize(size_t size, double elem) {
	if (size > _size) {
		reserve(size);
		for (size_t i = _size; i < size; ++i) {
			_data[i] = elem;
		}
		_size = _capacity;
	} else if (size < _size) {
		_size = size;
	}
}
bool Vector::operator==(const Vector &other) const {
	if (other.size() != size()) {
		return false;
	}
	for (size_t i = 0; i < size(); ++i) {
		if (data()[i] != other[i]) {
			return false;
		}
	}
	return true;
}
std::weak_ordering Vector::operator<=>(const Vector &other) const {
	if (other.size() != size()) {
		if (other.size() > size()) {
			return std::weak_ordering::less;
		} else {
			return std::weak_ordering::greater;
		}
	}
	for (size_t i = 0; i < size(); ++i) {
		if (data()[i] != other[i]) {
			if (data()[i] > other[i]) {
				return std::weak_ordering::greater;
			} else {
				return std::weak_ordering::less;
			}
		}
	}
	return std::weak_ordering::equivalent;
}

std::ostream &operator<<(std::ostream &ostream, const Vector &vector) {
	for (size_t i = 0; i < vector.size(); ++i) {
		ostream << vector[i] << " ";
	}
	return ostream;
}

double &Vector::Iterator::operator*() const { return *ptr; }
double *Vector::Iterator::operator->() { return ptr; }

Vector::Iterator &Vector::Iterator::operator++() {
	++ptr;
	return *this;
}
Vector::Iterator Vector::Iterator::operator++(int) {
	Iterator tmp = *this;
	++ptr;
	return tmp;
}

Vector::Iterator &Vector::Iterator::operator--()& {
	--ptr;
	return *this;
}
Vector::Iterator Vector::Iterator::operator--(int) {
	Iterator tmp = *this;
	--ptr;
	return tmp;
}

Vector::Iterator Vector::Iterator::operator+(difference_type n) const { return Iterator{ptr + n}; }

Vector::Iterator Vector::Iterator::operator-(difference_type n) const { return Iterator{ptr - n}; }

Vector::Iterator::difference_type Vector::Iterator::operator-(const Vector::Iterator &other) const { return ptr - other.ptr; }

bool Vector::Iterator::operator==(const Iterator &other) const { return ptr == other.ptr; }

bool Vector::Iterator::operator!=(const Iterator &other) const { return ptr != other.ptr; }

Vector::Iterator &Vector::Iterator::operator+=(difference_type n) & {
	*this = *this + n;
	return *this;
}
Vector::Iterator &Vector::Iterator::operator-=(difference_type n) & {
	*this = *this - n;
	return *this;
}
std::weak_ordering Vector::Iterator::operator<=>(const Vector::Iterator &other) const {
	if (ptr > other.ptr) {
		return std::weak_ordering::greater;
	}
	if (ptr < other.ptr) {
		return std::weak_ordering::less;
	}
	return std::weak_ordering::equivalent;
}
bool Vector::Iterator::operator<(const Vector::Iterator &other) const {
	return (*this <=> other) == std::weak_ordering::less;
}

bool Vector::Iterator::operator>(const Vector::Iterator &other) const {
	return (*this <=> other) == std::weak_ordering::greater;
}

Vector::Iterator Vector::begin() { return Vector::Iterator{_data}; }

Vector::Iterator Vector::end() { return Vector::Iterator{_data + _size}; }

Vector::Iterator Vector::cbegin() const { return Vector::Iterator{_data}; }

Vector::Iterator Vector::cend() const { return Vector::Iterator{_data + _size}; }

bool Vector::empty() const { return _size == 0; }

Vector::Vector(std::initializer_list<double> init) {
	_size = init.size();
	_capacity = _size;
	_data = new double[_size];
	std::copy(init.begin(), init.end(), _data);
}

Vector::Vector(const Vector &vector) {
	_size = vector._size;
	_capacity = vector._capacity;
	_data = new double [_size];
	std::memmove(_data, vector._data, _size);
}

Vector &Vector::operator=(const Vector &vector) {
	if(this != &vector){
		_size = vector.size();
		_capacity = vector.capacity();
		_data = vector._data;
	}
	return *this;
}

double &Vector::Iterator::operator[](size_t index) { return *(ptr + index); }

const double &Vector::Iterator::operator[](size_t index) const { return *(ptr + index); }

bool Vector::Iterator::operator<=(const Vector::Iterator &other) const {
	return (*this <=> other) == std::weak_ordering::less || (*this <=> other) == std::weak_ordering::equivalent;
}

bool Vector::Iterator::operator>=(const Vector::Iterator &other) const {
	return (*this <=> other) == std::weak_ordering::greater || (*this <=> other) == std::weak_ordering::equivalent;
}

