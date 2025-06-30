#include <iostream>
#include <string>
#include "iter.hpp"

// Regular functions for comparison
void printInt(int& n) { std::cout << n << " "; }
void printString(std::string& s) { std::cout << s << " "; }

int main() {
    std::cout << "=== Testing iter with different function types ===" << std::endl;
    
    int intArray[] = {1, 2, 3, 4, 5};
    
    // Test 1: Regular function
    std::cout << "Test 1 - Regular function:" << std::endl;
    std::cout << "Original: ";
    iter(intArray, 5, printInt);
    std::cout << std::endl;
    
    // Test 2: Template function instantiation
    std::cout << "Test 2 - Template function:" << std::endl;
    std::cout << "Using print<int>: ";
    iter(intArray, 5, print<int>);
    std::cout << std::endl;
    
    // Test 3: Template function that modifies
    std::cout << "Test 3 - Modifying template function:" << std::endl;
    std::cout << "Before square: ";
    iter(intArray, 5, print<int>);
    std::cout << std::endl;
    
    iter(intArray, 5, square<int>);  // ← Demonstrates template instantiation!
    
    std::cout << "After square:  ";
    iter(intArray, 5, print<int>);
    std::cout << std::endl;
    
    // Test 4: Different types with templates
    std::cout << "Test 4 - String array with templates:" << std::endl;
    std::string strings[] = {"Hello", "World", "Templates"};
    iter(strings, 3, print<std::string>);
    std::cout << std::endl;
    
    return 0;
}