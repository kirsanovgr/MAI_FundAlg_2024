#include <iostream>
#include <stdexcept> // исключения
#include <cstddef>   // size_t

class vector {
private:
    size_t _size;       // Текущее количество элементов
    size_t _capacity;   // Вместимость массива
    double* _data;      // Указатель на массив данных

    void reallocate(size_t new_capacity) {
        double* new_data = new double[new_capacity];
        for (size_t i = 0; i < _size; ++i) {
            new_data[i] = _data[i];
        }
        delete[] _data;
        _data = new_data;
        _capacity = new_capacity;
    }

public:
    // конструкторы
    vector(size_t count, double value = 0.0) : _size(count), _capacity(count), _data(new double[count]) {
        for (size_t i = 0; i < count; ++i) {
            _data[i] = value;
        }
    }

    vector(size_t count) : vector(count, 0.0) {}

    vector(const vector& other) : _size(other._size), _capacity(other._capacity), _data(new double[other._capacity]) {
        for (size_t i = 0; i < other._size; ++i) {
            _data[i] = other._data[i];
        }
    }

    vector& operator=(const vector& other) {
        if (this != &other) {
            delete[] _data;
            _size = other._size;
            _capacity = other._capacity;
            _data = new double[_capacity];
            for (size_t i = 0; i < _size; ++i) {
                _data[i] = other._data[i];
            }
        }
        return *this;
    }

    ~vector() {
        delete[] _data;
    }

    // методы
    double& at(size_t index) {
        if (index >= _size) {
            throw std::out_of_range("Index out of range");
        }
        return _data[index];
    }

    const double& at(size_t index) const {
        if (index >= _size) {
            throw std::out_of_range("Index out of range");
        }
        return _data[index];
    }

    double& front() {
        return at(0);
    }

    const double& front() const {
        return at(0);
    }

    double& back() {
        return at(_size - 1);
    }

    const double& back() const {
        return at(_size - 1);
    }

    double* data() {
        return _data;
    }

    const double* data() const {
        return _data;
    }

    bool empty() const {
        return _size == 0;
    }

    size_t size() const {
        return _size;
    }

    void reserve(size_t num) {
        if (num > _capacity) {
            reallocate(num);
        }
    }

    size_t capacity() const {
        return _capacity;
    }

    void shrink_to_fit() {
        if (_capacity > _size) {
            reallocate(_size);
        }
    }

    void clear() {
        _size = 0;
    }

    void insert(size_t index, double elem) {
        if (index > _size) {
            throw std::out_of_range("Index out of range");
        }
        if (_size == _capacity) {
            reserve(_capacity == 0 ? 1 : _capacity * 2);
        }
        for (size_t i = _size; i > index; --i) {
            _data[i] = _data[i - 1];
        }
        _data[index] = elem;
        ++_size;
    }

    void erase(size_t index) {
        if (index >= _size) {
            throw std::out_of_range("Index out of range");
        }
        for (size_t i = index; i < _size - 1; ++i) {
            _data[i] = _data[i + 1];
        }
        --_size;
    }

    void push_back(double elem) {
        if (_size == _capacity) {
            reserve(_capacity == 0 ? 1 : _capacity * 2);
        }
        _data[_size++] = elem;
    }

    void pop_back() {
        if (_size > 0) {
            --_size;
        }
    }

    void resize(size_t new_size, double elem = 0.0) {
        if (new_size > _capacity) {
            reserve(new_size);
        }
        for (size_t i = _size; i < new_size; ++i) {
            _data[i] = elem;
        }
        _size = new_size;
    }

    bool operator==(const vector& other) const {
        if (_size != other._size) return false;
        for (size_t i = 0; i < _size; ++i) {
            if (_data[i] != other._data[i]) return false;
        }
        return true;
    }

    bool operator!=(const vector& other) const {
        return !(*this == other);
    }

    bool operator<(const vector& other) const {
        for (size_t i = 0; i < std::min(_size, other._size); ++i) {
            if (_data[i] < other._data[i]) return true;
            if (_data[i] > other._data[i]) return false;
        }
        return _size < other._size;
    }

    bool operator<=(const vector& other) const {
        return *this < other || *this == other;
    }

    bool operator>(const vector& other) const {
        return !(*this <= other);
    }

    bool operator>=(const vector& other) const {
        return !(*this < other);
    }

    class iterator {
    private:
        double* _ptr;

    public:
        explicit iterator(double* ptr) : _ptr(ptr) {}

        double& operator*() const {
            return *_ptr;
        }

        iterator& operator++() {
            ++_ptr;
            return *this;
        }

        iterator operator++(int) {
            iterator temp = *this;
            ++(*this);
            return temp;
        }

        bool operator==(const iterator& other) const {
            return _ptr == other._ptr;
        }

        bool operator!=(const iterator& other) const {
            return _ptr != other._ptr;
        }
    };

    iterator begin() {
        return iterator(_data);
    }

    iterator end() {
        return iterator(_data + _size);
    }
};
