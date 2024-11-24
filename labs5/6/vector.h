#ifndef VECTOR_H
#define VECTOR_H

#include <stdexcept>
#include <initializer_list>
#include <iterator>
#if __cplusplus >= 202002L
#include <compare>
#endif

class vector {
public:
    class iterator {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = double;
        using pointer = double*;
        using reference = double&;

        iterator(pointer ptr) : _ptr(ptr) {}

        reference operator*() const { return *_ptr; }
        pointer operator->() { return _ptr; }

        iterator& operator++() { ++_ptr; return *this; }
        iterator operator++(int) { iterator tmp = *this; ++(*this); return tmp; }

        iterator& operator--() { --_ptr; return *this; }
        iterator operator--(int) { iterator tmp = *this; --(*this); return tmp; }

        iterator& operator+=(difference_type offset) { _ptr += offset; return *this; }
        iterator operator+(difference_type offset) const { return iterator(_ptr + offset); }

        iterator& operator-=(difference_type offset) { _ptr -= offset; return *this; }
        iterator operator-(difference_type offset) const { return iterator(_ptr - offset); }

        difference_type operator-(const iterator& other) const { return _ptr - other._ptr; }

        bool operator==(const iterator& other) const { return _ptr == other._ptr; }
        bool operator!=(const iterator& other) const { return _ptr != other._ptr; }
        bool operator<(const iterator& other) const { return _ptr < other._ptr; }
        bool operator<=(const iterator& other) const { return _ptr <= other._ptr; }
        bool operator>(const iterator& other) const { return _ptr > other._ptr; }
        bool operator>=(const iterator& other) const { return _ptr >= other._ptr; }

    private:
        pointer _ptr;
    };

    vector();
    vector(size_t count, double value = 0.0);
    vector(size_t count);
    vector(const double* first, const double* last);
    vector(std::initializer_list<double> init);

    ~vector();

    size_t size() const;
    size_t capacity() const;
    bool empty() const;
    void clear();
    double* data();
    const double* data() const;

    double& at(size_t index);
    const double& at(size_t index) const;
    double& front();
    const double& front() const;
    double& back();
    const double& back() const;
    void insert(size_t index, double elem);
    void erase(size_t index);
    void push_back(double elem);
    void pop_back();
    void resize(size_t size, double elem = 0.0);
    void reserve(size_t num);
    void shrink_to_fit();

    iterator begin();
    iterator end();
    const iterator begin() const;
    const iterator end() const;

#if __cplusplus >= 202002L
    auto operator<=>(const vector& other) const = default;
#endif
    bool operator==(const vector& other) const;
    bool operator!=(const vector& other) const;
    bool operator<(const vector& other) const;
    bool operator<=(const vector& other) const;
    bool operator>(const vector& other) const;
    bool operator>=(const vector& other) const;

    void check_index(size_t index) const;
    void handle_memory_allocation_failure() const;

private:
    size_t _size;
    size_t _capacity;
    double* _data;

    void allocate(size_t new_capacity);
    void deallocate();
};

#endif