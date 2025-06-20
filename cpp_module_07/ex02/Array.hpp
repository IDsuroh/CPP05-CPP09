#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <iostream>
#include <exception>
#include <cstddef>

template <typename T>
class Array {
private:
    T* _data;
    std::size_t _size;

public:
    Array();
    Array(unsigned int n);
    Array(const Array<T>& other);
    Array<T>& operator=(const Array<T>& other);
    ~Array();
    
    T& operator[](std::size_t idx);
    const T& operator[](std::size_t idx) const;
    std::size_t size() const;
    
    class OutOfBoundsException : public std::exception {
    public:
        virtual const char* what() const throw() {
            return "Array index out of bounds";
        }
    };
};

#include "Array.tpp"

#endif