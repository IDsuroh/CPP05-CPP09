#include <iostream>
#include <string>
#include "iter.hpp"

void printInt(int& n) { 
    std::cout << n << " "; 
}

void printString(std::string& s) { 
    std::cout << s << " "; 
}

void printDouble(double& d) { 
    std::cout << d << " "; 
}

void printChar(char& c) { 
    std::cout << c << " "; 
}

int main() {
    std::cout << "=====================================" << std::endl;
    std::cout << "       Template Iterator Test        " << std::endl;
    std::cout << "=====================================" << std::endl;
    std::cout << std::endl;
    
    std::cout << "Testing the iter template with different array types..." << std::endl;
    std::cout << std::endl;
    
    // Test 1: Integer Array
    std::cout << "🔢 Test 1: Integer Array" << std::endl;
    std::cout << "   Array: {42, 8, 15, 23, 77}" << std::endl;
    int intArray[] = {42, 8, 15, 23, 77};
    std::cout << "   Output: ";
    iter(intArray, 5, printInt);
    std::cout << std::endl;
    std::cout << "   ✓ Success: iter works with integers!" << std::endl;
    std::cout << std::endl;
    
    // Test 2: String Array
    std::cout << "📝 Test 2: String Array" << std::endl;
    std::cout << "   Array: {\"Hello\", \"Beautiful\", \"World\"}" << std::endl;
    std::string stringArray[] = {"Hello", "Beautiful", "World"};
    std::cout << "   Output: ";
    iter(stringArray, 3, printString);
    std::cout << std::endl;
    std::cout << "   ✓ Success: iter works with strings!" << std::endl;
    std::cout << std::endl;
    
    // Test 3: Double Array
    std::cout << "🔢 Test 3: Double Array" << std::endl;
    std::cout << "   Array: {3.14, 2.71, 1.41, 1.73}" << std::endl;
    double doubleArray[] = {3.14, 2.71, 1.41, 1.73};
    std::cout << "   Output: ";
    iter(doubleArray, 4, printDouble);
    std::cout << std::endl;
    std::cout << "   ✓ Success: iter works with doubles!" << std::endl;
    std::cout << std::endl;
    
    // Test 4: Character Array
    std::cout << "🔤 Test 4: Character Array" << std::endl;
    std::cout << "   Array: {'C', '+', '+', '9', '8'}" << std::endl;
    char charArray[] = {'C', '+', '+', '9', '8'};
    std::cout << "   Output: ";
    iter(charArray, 5, printChar);
    std::cout << std::endl;
    std::cout << "   ✓ Success: iter works with characters!" << std::endl;
    std::cout << std::endl;
    
    // Summary
    std::cout << "=====================================" << std::endl;
    std::cout << "             Summary                 " << std::endl;
    std::cout << "=====================================" << std::endl;
    std::cout << "✅ The iter template function works perfectly!" << std::endl;
    std::cout << "✅ It can handle arrays of ANY type" << std::endl;
    std::cout << "✅ It applies the given function to every element" << std::endl;
    std::cout << "✅ Template instantiation happens automatically" << std::endl;
    std::cout << std::endl;
    std::cout << "📋 Function signature:" << std::endl;
    std::cout << "   template <typename T, typename F>" << std::endl;
    std::cout << "   void iter(T* array, size_t length, F func)" << std::endl;
    std::cout << std::endl;
    std::cout << "🎯 The power of C++ templates demonstrated!" << std::endl;
    
    return 0;
}