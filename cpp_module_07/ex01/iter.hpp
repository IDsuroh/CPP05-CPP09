#ifndef ITER_HPP
#define ITER_HPP

#include <iostream>

// Main template function: iter
template <typename T, typename F>
void iter(T* array, size_t length, F func) {
    for (size_t i = 0; i < length; i++) {
        func(array[i]);
    }
}

// const version
template <typename T>
void iter(const T* array, size_t length, void (*func)(const T&)) {
    for (size_t i = 0; i < length; i++) {
        func(array[i]);
    }
}

// Helper template functions for testing
template <typename T>
void print(const T& element) {
    std::cout << element << " ";
}

template <typename T>
void square(T& n) {
    n = n * n;
}

#endif
