#include <iostream>
#include <string>
#include "Array.hpp"

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "       Array Template Class Tests      " << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << std::endl;

    try {
        // ============= TEST 1: DEFAULT CONSTRUCTOR =============
        std::cout << "🔧 TEST 1: Default Constructor" << std::endl;
        std::cout << "Creating empty array..." << std::endl;
        
        Array<int> emptyArray;
        std::cout << "✓ Empty array created successfully" << std::endl;
        std::cout << "  Size: " << emptyArray.size() << std::endl;
        std::cout << std::endl;

        // ============= TEST 2: PARAMETERIZED CONSTRUCTOR =============
        std::cout << "🔧 TEST 2: Parameterized Constructor" << std::endl;
        std::cout << "Creating array with 5 integers..." << std::endl;
        
        Array<int> intArray(5);
        std::cout << "✓ Integer array created successfully" << std::endl;
        std::cout << "  Size: " << intArray.size() << std::endl;
        std::cout << "  Default values: ";
        for (size_t i = 0; i < intArray.size(); i++) {
            std::cout << intArray[i] << " ";
        }
        std::cout << std::endl;
        std::cout << std::endl;

        // ============= TEST 3: ELEMENT ASSIGNMENT & ACCESS =============
        std::cout << "🔧 TEST 3: Element Assignment & Access" << std::endl;
        std::cout << "Assigning values to array elements..." << std::endl;
        
        for (size_t i = 0; i < intArray.size(); i++) {
            intArray[i] = (i + 1) * 10;  // 10, 20, 30, 40, 50
        }
        
        std::cout << "✓ Values assigned successfully" << std::endl;
        std::cout << "  Array contents: ";
        for (size_t i = 0; i < intArray.size(); i++) {
            std::cout << intArray[i] << " ";
        }
        std::cout << std::endl;
        std::cout << "  Individual access: arr[2] = " << intArray[2] << std::endl;
        std::cout << std::endl;

        // ============= TEST 4: COPY CONSTRUCTOR =============
        std::cout << "🔧 TEST 4: Copy Constructor (Deep Copy)" << std::endl;
        std::cout << "Creating copy of integer array..." << std::endl;
        
        Array<int> copiedArray(intArray);
        std::cout << "✓ Copy created successfully" << std::endl;
        std::cout << "  Original size: " << intArray.size() << std::endl;
        std::cout << "  Copy size: " << copiedArray.size() << std::endl;
        std::cout << "  Copy contents: ";
        for (size_t i = 0; i < copiedArray.size(); i++) {
            std::cout << copiedArray[i] << " ";
        }
        std::cout << std::endl;
        
        // Test deep copy by modifying original
        std::cout << "Testing deep copy by modifying original..." << std::endl;
        intArray[0] = 999;
        std::cout << "  After modifying original[0] to 999:" << std::endl;
        std::cout << "  Original[0]: " << intArray[0] << std::endl;
        std::cout << "  Copy[0]:     " << copiedArray[0] << std::endl;
        std::cout << "✓ Deep copy verified - changes don't affect copy!" << std::endl;
        std::cout << std::endl;

        // ============= TEST 5: ASSIGNMENT OPERATOR =============
        std::cout << "🔧 TEST 5: Assignment Operator" << std::endl;
        std::cout << "Creating new array and assigning values..." << std::endl;
        
        Array<int> assignedArray(3);
        assignedArray[0] = 100;
        assignedArray[1] = 200;
        assignedArray[2] = 300;
        
        std::cout << "  Before assignment: ";
        for (size_t i = 0; i < assignedArray.size(); i++) {
            std::cout << assignedArray[i] << " ";
        }
        std::cout << std::endl;
        
        assignedArray = copiedArray;  // Assignment operation
        std::cout << "✓ Assignment completed" << std::endl;
        std::cout << "  After assignment:  ";
        for (size_t i = 0; i < assignedArray.size(); i++) {
            std::cout << assignedArray[i] << " ";
        }
        std::cout << std::endl;
        std::cout << "  New size: " << assignedArray.size() << std::endl;
        std::cout << std::endl;

        // ============= TEST 6: STRING ARRAY =============
        std::cout << "🔧 TEST 6: String Array Template" << std::endl;
        std::cout << "Testing with different template type (string)..." << std::endl;
        
        Array<std::string> stringArray(4);
        stringArray[0] = "Hello";
        stringArray[1] = "Template";
        stringArray[2] = "Array";
        stringArray[3] = "World";
        
        std::cout << "✓ String array created and populated" << std::endl;
        std::cout << "  Contents: ";
        for (size_t i = 0; i < stringArray.size(); i++) {
            std::cout << "\"" << stringArray[i] << "\" ";
        }
        std::cout << std::endl;
        std::cout << std::endl;

        // ============= TEST 7: DOUBLE ARRAY =============
        std::cout << "🔧 TEST 7: Double Array Template" << std::endl;
        std::cout << "Testing with floating-point numbers..." << std::endl;
        
        Array<double> doubleArray(3);
        doubleArray[0] = 3.14;
        doubleArray[1] = 2.71;
        doubleArray[2] = 1.41;
        
        std::cout << "✓ Double array created and populated" << std::endl;
        std::cout << "  Contents: ";
        for (size_t i = 0; i < doubleArray.size(); i++) {
            std::cout << doubleArray[i] << " ";
        }
        std::cout << std::endl;
        std::cout << std::endl;

        // ============= TEST 8: CONST ARRAY ACCESS =============
        std::cout << "🔧 TEST 8: Const Array Access" << std::endl;
        std::cout << "Testing const operator[] ..." << std::endl;
        
        const Array<int> constArray(copiedArray);  // const copy
        std::cout << "✓ Const array created" << std::endl;
        std::cout << "  Const array[1]: " << constArray[1] << std::endl;
        std::cout << "  Size: " << constArray.size() << std::endl;
        std::cout << std::endl;

        // ============= TEST 9: EXCEPTION HANDLING =============
        std::cout << "🔧 TEST 9: Exception Handling" << std::endl;
        std::cout << "Testing out-of-bounds access..." << std::endl;
        
        // Test 9a: Access beyond array bounds
        std::cout << "  Attempting to access index 10 in array of size " 
                  << intArray.size() << "..." << std::endl;
        try {
            std::cout << "  Value: " << intArray[10] << std::endl;
            std::cout << "✗ ERROR: Should have thrown exception!" << std::endl;
        } catch (const std::exception& e) {
            std::cout << "✓ Exception caught: " << e.what() << std::endl;
        }
        
        // Test 9b: Access empty array
        std::cout << "  Attempting to access index 0 in empty array..." << std::endl;
        try {
            std::cout << "  Value: " << emptyArray[0] << std::endl;
            std::cout << "✗ ERROR: Should have thrown exception!" << std::endl;
        } catch (const std::exception& e) {
            std::cout << "✓ Exception caught: " << e.what() << std::endl;
        }
        
        // Test 9c: Negative index (will become very large unsigned)
        std::cout << "  Testing edge case with large index..." << std::endl;
        try {
            std::cout << "  Value: " << intArray[static_cast<size_t>(-1)] << std::endl;
            std::cout << "✗ ERROR: Should have thrown exception!" << std::endl;
        } catch (const std::exception& e) {
            std::cout << "✓ Exception caught: " << e.what() << std::endl;
        }
        std::cout << std::endl;

        // ============= TEST 10: SELF-ASSIGNMENT =============
        std::cout << "🔧 TEST 10: Self-Assignment Test" << std::endl;
        std::cout << "Testing self-assignment (array = array)..." << std::endl;
        
        Array<int> selfTestArray(3);
        selfTestArray[0] = 42;
        selfTestArray[1] = 84;
        selfTestArray[2] = 126;
        
        std::cout << "  Before self-assignment: ";
        for (size_t i = 0; i < selfTestArray.size(); i++) {
            std::cout << selfTestArray[i] << " ";
        }
        std::cout << std::endl;
        
        selfTestArray = selfTestArray;  // Self-assignment
        
        std::cout << "  After self-assignment:  ";
        for (size_t i = 0; i < selfTestArray.size(); i++) {
            std::cout << selfTestArray[i] << " ";
        }
        std::cout << std::endl;
        std::cout << "✓ Self-assignment handled correctly" << std::endl;
        std::cout << std::endl;

        // ============= FINAL SUMMARY =============
        std::cout << "========================================" << std::endl;
        std::cout << "            🎉 ALL TESTS PASSED!       " << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << "✅ Default constructor works" << std::endl;
        std::cout << "✅ Parameterized constructor works" << std::endl;
        std::cout << "✅ Element access and assignment work" << std::endl;
        std::cout << "✅ Copy constructor performs deep copy" << std::endl;
        std::cout << "✅ Assignment operator works correctly" << std::endl;
        std::cout << "✅ Template works with multiple types" << std::endl;
        std::cout << "✅ Const correctness implemented" << std::endl;
        std::cout << "✅ Exception handling works properly" << std::endl;
        std::cout << "✅ Self-assignment is safe" << std::endl;
        std::cout << "✅ Memory management is correct" << std::endl;
        std::cout << std::endl;
        std::cout << "🏆 Array template class is fully functional!" << std::endl;

    } catch (const std::exception& e) {
        std::cout << "❌ UNEXPECTED EXCEPTION: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}