// main.cpp
#include "Bureaucrat.hpp"
#include <iostream>

int main() {
    std::cout << "=== Valid Creation & Basic Operations ===\n";
    try {
        Bureaucrat john("John Doe", 75);
        std::cout << john << std::endl;

        john.increment();
        std::cout << "After increment: " << john << std::endl;

        john.decrement();
        std::cout << "After decrement: " << john << "\n\n";
    }
    catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n\n";
    }

    std::cout << "=== Copy Constructor Test ===\n";
    try {
        Bureaucrat original("Original", 42);
        Bureaucrat copyConstructed(original);
        std::cout << "Original: "       << original       << "\n"
                  << "Copy-constructed: " << copyConstructed << "\n\n";
    }
    catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n\n";
    }

    std::cout << "=== Assignment Operator Test ===\n";
    try {
        Bureaucrat a("A", 30);
        Bureaucrat b("B", 100);
        std::cout << "Before assignment:\n"
                  << "  a: " << a << "\n"
                  << "  b: " << b << "\n";

        b = a;
        std::cout << "After b = a:\n"
                  << "  a: " << a << "\n"
                  << "  b: " << b << "\n\n";
    }
    catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n\n";
    }

    std::cout << "=== Boundary Increment at Grade 1 ===\n";
    try {
        Bureaucrat top("Top", 1);
        std::cout << top << std::endl;
        top.increment();  // should throw
    }
    catch (std::exception& e) {
        std::cerr << "Expected exception: " << e.what() << "\n\n";
    }

    std::cout << "=== Boundary Decrement at Grade 150 ===\n";
    try {
        Bureaucrat bottom("Bottom", 150);
        std::cout << bottom << std::endl;
        bottom.decrement();  // should throw
    }
    catch (std::exception& e) {
        std::cerr << "Expected exception: " << e.what() << "\n\n";
    }

    std::cout << "=== Invalid Construction (Too High) ===\n";
    try {
        Bureaucrat tooHigh("TooHigh", 0);  // should throw
    }
    catch (std::exception& e) {
        std::cerr << "Expected exception: " << e.what() << "\n\n";
    }

    std::cout << "=== Invalid Construction (Too Low) ===\n";
    try {
        Bureaucrat tooLow("TooLow", 151);  // should throw
    }
    catch (std::exception& e) {
        std::cerr << "Expected exception: " << e.what() << "\n";
    }

    return 0;
}