#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Span.hpp"

int main() {
    std::cout << "=== Basic Test ===" << std::endl;
    
    // Test from the exercise
    try {
        Span sp = Span(5);
        sp.addNumber(6);
        sp.addNumber(3);
        sp.addNumber(17);
        sp.addNumber(9);
        sp.addNumber(11);
        std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
        std::cout << "Longest span: " << sp.longestSpan() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    
    std::cout << "\n=== Exception Tests ===" << std::endl;
    
    // Test span full exception
    try {
        Span sp(2);
        sp.addNumber(1);
        sp.addNumber(2);
        sp.addNumber(3); // Should throw
    } catch (const std::exception& e) {
        std::cout << "Caught expected exception: " << e.what() << std::endl;
    }
    
    // Test no span exception (empty)
    try {
        Span sp(5);
        sp.shortestSpan(); // Should throw
    } catch (const std::exception& e) {
        std::cout << "Caught expected exception: " << e.what() << std::endl;
    }
    
    // Test no span exception (one element)
    try {
        Span sp(5);
        sp.addNumber(42);
        sp.longestSpan(); // Should throw
    } catch (const std::exception& e) {
        std::cout << "Caught expected exception: " << e.what() << std::endl;
    }
    
    std::cout << "\n=== Iterator Range Test ===" << std::endl;
    
    // Test adding with iterators
    try {
        std::vector<int> numbers;
        for (int i = 0; i < 10; ++i) {
            numbers.push_back(i * 10);
        }
        
        Span sp(15);
        sp.addNumber(numbers.begin(), numbers.end());
        sp.addNumber(5);
        sp.addNumber(25);
        
        std::cout << "Added " << sp.size() << " numbers" << std::endl;
        std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
        std::cout << "Longest span: " << sp.longestSpan() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    
    std::cout << "\n=== Large Test (10,000+ numbers) ===" << std::endl;
    
    // Test with large number of elements
    try {
        const unsigned int largeSize = 15000;
        Span largeSpan(largeSize);
        
        // Generate random numbers
        std::srand(std::time(0));
        std::vector<int> largeNumbers;
        largeNumbers.reserve(largeSize);
        
        for (unsigned int i = 0; i < largeSize; ++i) {
            largeNumbers.push_back(std::rand() % 100000);
        }
        
        // Add all at once using iterators
        largeSpan.addNumber(largeNumbers.begin(), largeNumbers.end());
        
        std::cout << "Successfully added " << largeSpan.size() << " numbers" << std::endl;
        std::cout << "Shortest span: " << largeSpan.shortestSpan() << std::endl;
        std::cout << "Longest span: " << largeSpan.longestSpan() << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    
    std::cout << "\n=== Edge Case Tests ===" << std::endl;
    
    // Test with negative numbers
    try {
        Span sp(5);
        sp.addNumber(-10);
        sp.addNumber(-5);
        sp.addNumber(0);
        sp.addNumber(5);
        sp.addNumber(10);
        
        std::cout << "With negative numbers:" << std::endl;
        std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
        std::cout << "Longest span: " << sp.longestSpan() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    
    // Test with duplicate numbers
    try {
        Span sp(4);
        sp.addNumber(5);
        sp.addNumber(5);
        sp.addNumber(10);
        sp.addNumber(10);
        
        std::cout << "With duplicates:" << std::endl;
        std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
        std::cout << "Longest span: " << sp.longestSpan() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    
    return 0;
}