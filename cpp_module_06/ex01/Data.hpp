#ifndef DATA_HPP
#define DATA_HPP

#include <string>

struct Data {
    int id;
    std::string name;
    double value;
    char grade;
    
    // Constructor for easy testing
    Data(int i, const std::string& n, double v, char g) 
        : id(i), name(n), value(v), grade(g) {}
    
    // Default constructor
    Data()
        : id(0), name(""), value(0.0), grade('F') {}
};

#endif

/*

===Why Do We Need a Data.hpp File?===
The Data structure represents the complex data we want to
serialize.

The Problem:

// Without a Data structure, what would we serialize?
int x = 42;           // Just a number - boring!
std::string s = "hi"; // Just text - simple!

// With Data structure - more realistic:
struct Data {
    int id;           // Multiple pieces of information
    std::string name; // Different data types
    double value;     // Complex object in memory
    char grade;
};


===Why It Matters:===
// This is what actually happens in memory:
Data myData(42, "Alice", 3.14, 'A');

// Memory layout (simplified):
// Address: 0x1000  [42]         (int id)
// Address: 0x1008  [ptr to "Alice"] (string name)  
// Address: 0x1010  [3.14]       (double value)
// Address: 0x1018  ['A']        (char grade)

// The serialize/deserialize preserves access to ALL this data!



===What Do serialize() and deserialize() Actually Do?===

serialize() Function:

uintptr_t serialize(Data* ptr) {
    return reinterpret_cast<uintptr_t>(ptr);
}

What it does: Converts a memory address (pointer) into a
number

deserialize() Function:
Data* deserialize(uintptr_t raw) {
    return reinterpret_cast<Data*>(raw);
}

What it does: Converts a number back into
a memory address (pointer)

// Example:
uintptr_t number = 140734799816364;  // The serialized number

Data* ptr = deserialize(number);     // ptr = 0x7fff5fbff6ac
//                                   // (back to original address!)

// Memory addresses are just numbers!
Your computer's memory:
Address 0x1000: [some data]
Address 0x1001: [some data]  
Address 0x1002: [some data]
...

A pointer is just storing one of these address numbers
serialize() extracts that number
deserialize() puts it back into a pointer


===What is uintptr_t?===
uintptr_t = "Unsigned Integer Pointer Type"
#include <stdint.h>

uintptr_t is an integer type that can hold any pointer
- Guaranteed to be big enough to store a memory address
- On 64-bit systems: 64 bits (can hold addresses like 0x7fff5fbff6ac)
- On 32-bit systems: 32 bits (can hold addresses like 0x12345678)

Why Not Just Use int or long?
// Problem: Different systems have different pointer sizes

// 32-bit system:
void* ptr = malloc(10);
int address = (int)ptr;        // ✓ Works (32-bit int, 32-bit pointer)

// 64-bit system:  
void* ptr = malloc(10);
int address = (int)ptr;        // ✗ PROBLEM! (32-bit int, 64-bit pointer)
//                             // Lost information!

// Solution: uintptr_t adapts to your system
uintptr_t address = (uintptr_t)ptr;  // ✓ Always works!

*/