#ifndef ARRAY_TPP
#define ARRAY_TPP

#include <cstddef>
#include <stdexcept>

template<typename T>
Array<T>::Array()
    : _data(NULL), _size(0)
{}

template<typename T>
Array<T>::Array(unsigned int n)
    : _data(n ? new T[n]() : NULL), _size(n)
{}

template<typename T>
Array<T>::Array(const Array<T>& other)
    : _data(other._size ? new T[other._size] : NULL)
    , _size(other._size)
{
    for (std::size_t i = 0; i < _size; ++i)
        _data[i] = other._data[i];
}

template<typename T>
Array<T>& Array<T>::operator=(const Array<T>& other) {
    if (this != &other) {
        delete[] _data;
        _size = other._size;
        _data = _size ? new T[_size]() : NULL;
        for (std::size_t i = 0; i < _size; ++i)
            _data[i] = other._data[i];
    }
    return *this;
}

template<typename T>
Array<T>::~Array() {
    delete[] _data;
}

template<typename T>
T& Array<T>::operator[](std::size_t idx) {
    if (idx >= _size)
        throw std::out_of_range("Array index out of range");
    return _data[idx];
}

template<typename T>
const T& Array<T>::operator[](std::size_t idx) const {
    if (idx >= _size)
        throw std::out_of_range("Array index out of range");
    return _data[idx];
}

template<typename T>
std::size_t Array<T>::size() const {
    return _size;
}

#endif