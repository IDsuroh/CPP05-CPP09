#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <iostream>     // For std::cout, std::endl (probably used in .tpp file)
#include <exception>    // For std::exception base class
#include <cstddef>      // For std::size_t type

template <typename T> // T is a place holder for the actual type. e.g. int string etc
class Array {   // the template makes the class generic which means it can work with any type
private:
    T* _data;
    std::size_t _size;

public:
    Array();
    Array(unsigned int n);
    Array(const Array<T>& other);
    Array<T>& operator=(const Array<T>& other);
    ~Array();
    
    T& operator[](std::size_t idx);     // returns a reference. e.g. arr[0] = 42
    const T& operator[](std::size_t idx) const; // Why two versions?: C++ function overloading based on const-ness
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