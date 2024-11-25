#include "vector.h"
#include <algorithm>
#include <stdexcept>

vector::vector() : _size(0), _capacity(0), _data(nullptr) {}

vector::vector(size_t count, double value) : _size(count), _capacity(count), _data(new double[count]) {
    std::fill(_data, _data + count, value);
}

vector::vector(size_t count) : vector(count, 0.0) {}

vector::vector(const double* first, const double* last) : _size(last - first), _capacity(last - first), _data(new double[_size]) {
    std::copy(first, last, _data);
}

vector::vector(std::initializer_list<double> init) : vector(init.begin(), init.end()) {}

vector::~vector() {
    deallocate();
}

size_t vector::size() const {
    return _size;
}

size_t vector::capacity() const {
    return _capacity;
}

bool vector::empty() const {
    return _size == 0;
}

void vector::clear() {
    _size = 0;
}

double* vector::data() {
    return _data;
}

const double* vector::data() const {
    return _data;
}

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
    if (empty()) {
        throw std::out_of_range("Vector is empty");
    }
    return _data[0];
}

const double& vector::front() const {
    if (empty()) {
        throw std::out_of_range("Vector is empty");
    }
    return _data[0];
}

double& vector::back() {
    if (empty()) {
        throw std::out_of_range("Vector is empty");
    }
    return _data[_size - 1];
}

const double& vector::back() const {
    if (empty()) {
        throw std::out_of_range("Vector is empty");
    }
    return _data[_size - 1];
}

void vector::insert(size_t index, double elem) {
    if (index > _size) {
        throw std::out_of_range("Index out of range");
    }
    if (_size == _capacity) {
        reserve(_capacity == 0 ? 1 : _capacity * 2);
    }
    std::move_backward(_data + index, _data + _size, _data + _size + 1);
    _data[index] = elem;
    ++_size;
}

void vector::erase(size_t index) {
    if (index >= _size) {
        throw std::out_of_range("Index out of range");
    }
    std::move(_data + index + 1, _data + _size, _data + index);
    --_size;
}

void vector::push_back(double elem) {
    if (_size == _capacity) {
        reserve(_capacity == 0 ? 1 : _capacity * 2);
    }
    _data[_size++] = elem;
}

void vector::pop_back() {
    if (empty()) {
        throw std::out_of_range("Vector is empty");
    }
    --_size;
}

void vector::resize(size_t size, double elem) {
    if (size > _capacity) {
        reserve(size);
    }
    if (size > _size) {
        std::fill(_data + _size, _data + size, elem);
    }
    _size = size;
}

void vector::reserve(size_t num) {
    if (num > _capacity) {
        allocate(num);
    }
}

void vector::shrink_to_fit() {
    if (_capacity > _size) {
        allocate(_size);
    }
}

void vector::allocate(size_t new_capacity) {
    double* new_data = new double[new_capacity];
    if (_data) {
        std::copy(_data, _data + _size, new_data);
        delete[] _data;
    }
    _data = new_data;
    _capacity = new_capacity;
}

void vector::deallocate() {
    delete[] _data;
    _data = nullptr;
    _size = 0;
    _capacity = 0;
}

void vector::check_index(size_t index) const {
    if (index >= _size) {
        throw std::out_of_range("Index out of range");
    }
}

void vector::handle_memory_allocation_failure() const {
    if (!_data) {
        throw std::bad_alloc();
    }
}

vector::iterator vector::begin() {
    return iterator(_data);
}

vector::iterator vector::end() {
    return iterator(_data + _size);
}

const vector::iterator vector::begin() const {
    return iterator(_data);
}

const vector::iterator vector::end() const {
    return iterator(_data + _size);
}

#if __cplusplus < 202002L
bool vector::operator==(const vector& other) const {
    if (_size != other._size) {
        return false;
    }
    for (size_t i = 0; i < _size; ++i) {
        if (_data[i] != other._data[i]) {
            return false;
        }
    }
    return true;
}

bool vector::operator!=(const vector& other) const {
    return !(*this == other);
}

bool vector::operator<(const vector& other) const {
    return std::lexicographical_compare(_data, _data + _size, other._data, other._data + other._size);
}

bool vector::operator<=(const vector& other) const {
    return !(other < *this);
}

bool vector::operator>(const vector& other) const {
    return other < *this;
}

bool vector::operator>=(const vector& other) const {
    return !(*this < other);
}
#endif