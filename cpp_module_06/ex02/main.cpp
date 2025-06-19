#include "Base.hpp"
#include <iostream>

int main() {
    std::cout << "=== RUNTIME TYPE IDENTIFICATION DEMO ===" << std::endl;
    std::cout << "This program demonstrates polymorphism and RTTI in C++" << std::endl;
    std::cout << std::endl;
    
    // ========================================
    // STEP 1: Generate random objects
    // ========================================
    std::cout << "STEP 1: Generating random objects..." << std::endl;
    std::cout << "- generate() returns Base* but actual type is unknown until runtime" << std::endl;
    
    Base* mystery_obj1 = generate();
    Base* mystery_obj2 = generate();
    Base* mystery_obj3 = generate();
    Base* mystery_obj4 = generate();
    Base* mystery_obj5 = generate();
    
    std::cout << "- Created 5 objects, each could be A, B, or C" << std::endl;
    std::cout << "- We only have Base* pointers - actual types are hidden!" << std::endl;
    std::cout << std::endl;
    
    // ========================================
    // STEP 2: Identify using POINTER method
    // ========================================
    std::cout << "STEP 2: Identifying types using POINTER method" << std::endl;
    std::cout << "- Uses dynamic_cast<Type*> which returns NULL on failure" << std::endl;
    std::cout << "- Safe and simple - no exceptions thrown" << std::endl;
    std::cout << std::endl;
    
    std::cout << "Object 1 is type: ";
    identify(mystery_obj1);  // Calls identify(Base* p)
    
    std::cout << "Object 2 is type: ";
    identify(mystery_obj2);
    
    std::cout << "Object 3 is type: ";
    identify(mystery_obj3);
    
    std::cout << "Object 4 is type: ";
    identify(mystery_obj4);
    
    std::cout << "Object 5 is type: ";
    identify(mystery_obj5);
    
    std::cout << std::endl;
    
    // ========================================
    // STEP 3: Identify using REFERENCE method
    // ========================================
    std::cout << "STEP 3: Identifying types using REFERENCE method" << std::endl;
    std::cout << "- Uses dynamic_cast<Type&> which throws exceptions on failure" << std::endl;
    std::cout << "- More complex but demonstrates exception handling" << std::endl;
    std::cout << "- Notice: *obj converts pointer to reference" << std::endl;
    std::cout << std::endl;
    
    std::cout << "Object 1 (via reference) is type: ";
    identify(*mystery_obj1);  // Calls identify(Base& p) - note the *
    
    std::cout << "Object 2 (via reference) is type: ";
    identify(*mystery_obj2);
    
    std::cout << "Object 3 (via reference) is type: ";
    identify(*mystery_obj3);
    
    std::cout << "Object 4 (via reference) is type: ";
    identify(*mystery_obj4);
    
    std::cout << "Object 5 (via reference) is type: ";
    identify(*mystery_obj5);
    
    std::cout << std::endl;
    
    // ========================================
    // STEP 4: Demonstrate polymorphic container
    // ========================================
    std::cout << "STEP 4: Demonstrating polymorphic containers" << std::endl;
    std::cout << "- Storing different types in same container" << std::endl;
    std::cout << "- This is the power of polymorphism!" << std::endl;
    std::cout << std::endl;
    
    // Create array of Base pointers containing different types
    Base* mixed_objects[5] = {
        mystery_obj1, mystery_obj2, mystery_obj3, mystery_obj4, mystery_obj5
    };
    
    std::cout << "Processing mixed objects in a loop:" << std::endl;
    for (int i = 0; i < 5; i++) {
        std::cout << "  Array[" << i << "] contains type: ";
        identify(mixed_objects[i]);
        
        // Demonstrate type-specific behavior
        if (dynamic_cast<A*>(mixed_objects[i])) {
            std::cout << "    -> This is an A object - could do A-specific operations" << std::endl;
        }
        else if (dynamic_cast<B*>(mixed_objects[i])) {
            std::cout << "    -> This is a B object - could do B-specific operations" << std::endl;
        }
        else if (dynamic_cast<C*>(mixed_objects[i])) {
            std::cout << "    -> This is a C object - could do C-specific operations" << std::endl;
        }
    }
    
    std::cout << std::endl;
    
    // ========================================
    // STEP 5: Function overloading demonstration
    // ========================================
    std::cout << "STEP 5: Function overloading demonstration" << std::endl;
    std::cout << "- Same function name, different parameter types" << std::endl;
    std::cout << "- Compiler chooses correct version based on argument type" << std::endl;
    std::cout << std::endl;
    
    Base* test_obj = generate();
    std::cout << "Created test object..." << std::endl;
    
    std::cout << "Calling identify(test_obj):   ";
    identify(test_obj);    // Calls pointer version
    std::cout << "  ^ Used pointer version: identify(Base* p)" << std::endl;
    
    std::cout << "Calling identify(*test_obj):  ";
    identify(*test_obj);   // Calls reference version  
    std::cout << "  ^ Used reference version: identify(Base& p)" << std::endl;
    
    std::cout << std::endl;
    
    // ========================================
    // STEP 6: Memory cleanup
    // ========================================
    std::cout << "STEP 6: Cleaning up memory" << std::endl;
    std::cout << "- All objects were created with 'new', must be deleted" << std::endl;
    std::cout << "- Virtual destructor ensures proper cleanup" << std::endl;
    std::cout << std::endl;
    
    delete mystery_obj1;
    std::cout << "Deleted object 1" << std::endl;
    
    delete mystery_obj2;
    std::cout << "Deleted object 2" << std::endl;
    
    delete mystery_obj3;
    std::cout << "Deleted object 3" << std::endl;
    
    delete mystery_obj4;
    std::cout << "Deleted object 4" << std::endl;
    
    delete mystery_obj5;
    std::cout << "Deleted object 5" << std::endl;
    
    delete test_obj;
    std::cout << "Deleted test object" << std::endl;
    
    std::cout << std::endl;
    std::cout << "=== PROGRAM COMPLETED ===" << std::endl;
    std::cout << "Key concepts demonstrated:" << std::endl;
    std::cout << "1. Polymorphism - storing different types as Base*" << std::endl;
    std::cout << "2. RTTI - identifying actual type at runtime" << std::endl;
    std::cout << "3. dynamic_cast - safe type casting with pointers and references" << std::endl;
    std::cout << "4. Function overloading - same name, different parameters" << std::endl;
    std::cout << "5. Virtual destructors - proper cleanup in inheritance hierarchies" << std::endl;
    
    return 0;
}

/*

Purpose of the Exercise: Understanding Polymorphism and RTTI

1. Runtime Type Identification (RTTI)
- How to determine the actual type of an object at runtime when you only have a base
  class pointer/reference
- Understanding that compile-time type information can be different from runtime type information

2. Polymorphism in Action
- There is a Base* pointer, but it could be pointing to A, B, or C objects
- The actual type is only known at runtime, not compile time

3. Dynamic Casting
- Learning to use dynamic_cast to safely downcast from base to derived classes
- Understanding the difference between pointer and reference casting behavior

*/