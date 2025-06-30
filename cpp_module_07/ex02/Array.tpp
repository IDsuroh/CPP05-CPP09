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
    : _data(other._size ? new T[other._size] : NULL) , _size(other._size)
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
        throw OutOfBoundsException();
    return _data[idx];
}

template<typename T>
const T& Array<T>::operator[](std::size_t idx) const {
    if (idx >= _size)
        throw OutOfBoundsException();
    return _data[idx];
}

template<typename T>
std::size_t Array<T>::size() const {
    return _size;
}

#endif

/*
File Naming Convention
1. Why .tpp and not .cpp?
Extension	Meaning	Usage
.cpp	C++ source file	Regular class implementations
.hpp	Header file	Declarations
.tpp	Template implementation	Template implementations
.h	C header	C-style headers

Summary:        Key Differences
Aspect          Regular Classes/Functions	    Templates
Compilation     Compiled once to machine code	Compiled when
                                                    instantiated
Code Generation One function/class	            Multiple functions
                                                    & classes generated
Type Resolution	Runtime (sometimes)	            Compile-time
Error Detection	Runtime errors possible	        Most errors at
                                                    compile-time
Performance	    Function call overhead	        Often optimized away
Code Reuse	    Inheritance, virtual functions	Parametric polymorphism
Symbol Resolution	Link-time	                    Compile-time

The Core Difference
Regular code is "concrete"
- the compiler knows exactly what it's dealing with.

Template code is "abstract"
- it's a blueprint that becomes concrete only when the type parameter
is specified


Template Class (DOESN'T work with .hpp/.cpp):

// Array.hpp
template <typename T>
class Array {
public:
    void doSomething();  // Declaration
};

// Array.cpp  ❌ This WON'T work!
template <typename T>
void Array<T>::doSomething() {
    std::cout << "Implementation" << std::endl;
}

// main.cpp
#include "Array.hpp"   // Only sees declaration
Array<int> obj;
obj.doSomething();     // ❌ ERROR: Can't find Array<int>::doSomething()


2. Why template<typename T> before every function?
    Every template function definition must start with template<typename T>
    because each function is a separate template entity.

Without template<typename T>, the compiler sees:
Array<T>::Array() ❌ Error: What is T? Unknown type!

With template<typename T>, the compiler sees:
template<typename T>
Array<T>::Array() ✅ OK: T is a template parameter


3. Function Declaration Syntax: Array<T>::Array()
Array<T>::Array()
│     │   │
│     │   └─ Constructor name (same as class name)
│     └─ Template parameter specification  
└─ Class name


4. Why <T> before ::?
The <T> specifies which template instantiation that is being implemented.
Without <T>, compiler doesn't know what is the Array:
Array::Array() ❌ Array of what? Array<int>? Array<string>? Array<MyClass>?

With <T>, it's clear:
Array<T>::Array() ✅ Array of type T (whatever T is)
*/