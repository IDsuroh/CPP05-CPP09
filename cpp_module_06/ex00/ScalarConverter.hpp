#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <string>
#include <iostream>
#include <limits>
#include <cmath>
#include <iomanip>
#include <cstdlib>

enum InputType {
    TYPE_CHAR,
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_DOUBLE,
    TYPE_NAN,
    TYPE_PLUS_INF,
    TYPE_MINUS_INF,
    TYPE_INVALID
};

class ScalarConverter {
private:
    ScalarConverter();
    ScalarConverter(const ScalarConverter& other);
    ScalarConverter& operator=(const ScalarConverter& other);
    ~ScalarConverter();

    static InputType detectType(const std::string& str);

public:
    static void convert(const std::string& str);
};

#endif

/*

NaN (Not a Number)
    a special floating-point value that represents the result of
    undefined or impossible mathematical operations

    // What should these equal?
0 ÷ 0 = ?     // Undefined in mathematics
√(-1) = ?     // No real number solution  
log(-1) = ?   // Undefined for real numbers
∞ - ∞ = ?     // Indeterminate form

the additional f means float

"nan" → double NaN
"nanf" → float NaN (but stored as double in our case)
"+inf" → double positive infinity
"+inff" → float positive infinity
"-inf" → double negative infinity
"-inff" → float negative infinity

The static keyword is crucial for this specific project.

---1. Subject Requirement: Non-Instantiable Class---
Subject says: "As this class doesn't need to store anything at all,
                it must not be instantiable by users."

// Without static - needs an object:
ScalarConverter converter;    // ERROR: We don't want this!
converter.convert("42");      // Instance method call

// With static - no object needed:
ScalarConverter::convert("42");  // ✓ Direct class method call


---2. Utility/Helper Class Design Pattern---
The static makes ScalarConverter a utility class
                - like a namespace with functions:

// Similar to the use of standard library utilities:
std::abs(-5);           // Static-like utility function
std::max(10, 20);       // No object needed

// Our class works the same way:
ScalarConverter::convert("42");  // Utility function, no state needed

A utility class is a class that:

- Contains only static methods
- Has no instance variables (no state)
- Provides helper/convenience functions
- Cannot be instantiated


// Standard Library Examples:
std::numeric_limits<int>::max();     // Math utilities
std::sort(vec.begin(), vec.end());   // Algorithm utilities

// Our ScalarConverter:
class ScalarConverter {
    // Utility class for type conversion
private:
    ScalarConverter();  // Can't create instances
    
public:
    static void convert(const std::string& str);  // Pure function
};

// Math Utility Class Example:
class MathUtils {
private:
    MathUtils();  // Can't instantiate
    
public:
    static double square(double x) { return x * x; }
    static bool isPrime(int n) {  check if prime  }
    static double distance(double x1, double y1, double x2, double y2) {
        return sqrt(square(x2-x1) + square(y2-y1));
    }
};

// Usage:
double result = MathUtils::square(5);        // Just call the function
bool prime = MathUtils::isPrime(17);         // No object needed
double dist = MathUtils::distance(0,0,3,4);  // Pure calculation

Utility Class vs Abstract Class
Abstract Class
Purpose: Defines a contract/interface for derived classes to implement
Utility Class
Purpose: Provides standalone helper functions


---3. No State = No Instance Needed---
No State = No Instance Needed
What is "State"?
State = data that an object remembers between method calls

// CLASS WITH STATE (needs instances)
class BankAccount {
private:
    double balance;        // STATE: remembers balance
    std::string owner;     // STATE: remembers owner
    int accountNumber;     // STATE: remembers account number
    
public:
    void deposit(double amount) {
        balance += amount;  // MODIFIES STATE
    }
    
    double getBalance() {
        return balance;     // USES STATE
    }
};

// Usage - NEED instances because each has different state:
BankAccount alice;     // Alice's balance
BankAccount bob;       // Bob's balance (different from Alice's)
alice.deposit(100);    // Changes Alice's state only
bob.deposit(50);       // Changes Bob's state only

However,

class ScalarConverter {
    // NO member variables = NO STATE
    // Nothing to remember between calls
    
public:
    static void convert(const std::string& str) {
        // Takes input -> processes -> outputs
        // Doesn't remember anything
        // Each call is independent
    }
};

// No instances needed because there's nothing to store:
ScalarConverter::convert("42");   
        // Processes, outputs, forgets
ScalarConverter::convert("3.14"); 
        // Independent call, no memory of previous call


---4. Memory Efficiency---

// Without static (bad design):
void someFunction() {
    ScalarConverter conv1;     // Wastes memory
    ScalarConverter conv2;     // Wastes memory  
    ScalarConverter conv3;     // Wastes memory
    
    conv1.convert("42");
    conv2.convert("3.14");
    conv3.convert("'c'");
}

// With static (efficient):  
void someFunction() {
    ScalarConverter::convert("42");    // No memory allocation
    ScalarConverter::convert("3.14");  // No object creation
    ScalarConverter::convert("'c'");   // Direct function call
}
*/