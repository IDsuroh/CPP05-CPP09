#ifndef WHATEVER_HPP
#define WHATEVER_HPP

// Template function: swap
// Swaps the values of two parameters of any type T
template <typename T>
void swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

// Template function: min  
// Returns the smaller of two values
// If equal, returns the second one
template <typename T>
const T& min(const T& a, const T& b) {
    return (a < b) ? a : b;
}

// Template function: max
// Returns the larger of two values  
// If equal, returns the second one
template <typename T>
const T& max(const T& a, const T& b) {
    return (a > b) ? a : b;
}

#endif