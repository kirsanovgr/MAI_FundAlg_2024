#include "6.hpp"

// Вспомогательная функция для перевыделения памяти
void vector::reallocate(size_t new_capacity) {
    double* new_data = new double[new_capacity];
    if (_data) {
        std::memcpy(new_data, _data, _size * sizeof(double));
        delete[] _data;
    }
    _data = new_data;
    _capacity = new_capacity;
}

// Конструкторы
vector::vector() : _size(0), _capacity(0), _data(nullptr) {}

vector::vector(size_t count, double value) : _size(count), _capacity(count), _data(new double[count]) {
    std::fill(_data, _data + count, value);
}

vector::vector(size_t count) : _size(count), _capacity(count), _data(new double[count]) {}

vector::vector(const vector& other) : _size(other._size), _capacity(other._capacity), _data(new double[other._capacity]) {
    std::memcpy(_data, other._data, _size * sizeof(double));
}

vector& vector::operator=(const vector& other) {
    if (this != &other) {
        double* new_data = new double[other._capacity];
        std::memcpy(new_data, other._data, other._size * sizeof(double));
        delete[] _data;

        _data = new_data;
        _size = other._size;
        _capacity = other._capacity;
    }
    return *this;
}

vector::~vector() {
    delete[] _data;
}

// Методы доступа
double& vector::at(size_t index) {
    if (index >= _size) {
        throw std::out_of_range("Index out of range");
    }
    return _data[index];
}

const double& vector::at(size_t index) const {
    if (index >= _size) {
        throw std::out_of_range("Index out of range");
    }
    return _data[index];
}

double& vector::front() {
    return at(0);
}

const double& vector::front() const {
    return at(0);
}

double& vector::back() {
    return at(_size - 1);
}

const double& vector::back() const {
    return at(_size - 1);
}

double* vector::data() {
    return _data;
}

const double* vector::data() const {
    return _data;
}

// Информация о векторе
bool vector::empty() const {
    return _size == 0;
}

size_t vector::size() const {
    return _size;
}

size_t vector::capacity() const {
    return _capacity;
}

// Управление памятью
void vector::reserve(size_t num) {
    if (num > _capacity) {
        reallocate(num);
    }
}

void vector::shrink_to_fit() {
    if (_capacity > _size) {
        reallocate(_size);
    }
}

void vector::clear() {
    _size = 0;
}

// Модификация вектора
void vector::insert(size_t index, double elem) {
    if (index > _size) {
        throw std::out_of_range("Index out of range");
    }
    if (_size == _capacity) {
        reserve(_capacity == 0 ? 1 : _capacity * 2);
    }
    std::memmove(_data + index + 1, _data + index, (_size - index) * sizeof(double));
    _data[index] = elem;
    ++_size;
}

void vector::erase(size_t index) {
    if (index >= _size) {
        throw std::out_of_range("Index out of range");
    }
    std::memmove(_data + index, _data + index + 1, (_size - index - 1) * sizeof(double));
    --_size;
}

void vector::push_back(double elem) {
    if (_size == _capacity) {
        reserve(_capacity == 0 ? 1 : _capacity * 2);
    }
    _data[_size++] = elem;
}

void vector::pop_back() {
    if (_size > 0) {
        --_size;
    }
}

void vector::resize(size_t new_size, double elem) {
    if (new_size > _capacity) {
        reserve(new_size);
    }
    if (new_size > _size) {
        std::fill(_data + _size, _data + new_size, elem);
    }
    _size = new_size;
}

// Операторы
bool vector::operator==(const vector& other) const {
    if (_size != other._size) {
        return false;
    }
    return std::memcmp(_data, other._data, _size * sizeof(double)) == 0;
}

// Итераторы
vector::iterator vector::begin() {
    return _data;
}

vector::iterator vector::end() {
    return _data + _size;
}

vector::const_iterator vector::cbegin() const {
    return _data;
}

vector::const_iterator vector::cend() const {
    return _data + _size;
}
