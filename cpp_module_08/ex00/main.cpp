#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include "easyfind.hpp"

int main() {
    std::cout << "=== Testing easyfind with std::vector ===" << std::endl;
    
    // Test with vector
    std::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);
    
    try {
        std::vector<int>::iterator it = easyfind(vec, 3);
        std::cout << "Found value 3 at position: " << (it - vec.begin()) << std::endl;
        std::cout << "Value: " << *it << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    
    try {
        std::vector<int>::iterator it = easyfind(vec, 42);
        std::cout << "Found value 42 at position: " << (it - vec.begin()) << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Exception when searching for 42: " << e.what() << std::endl;
    }
    
    std::cout << "\n=== Testing easyfind with std::list ===" << std::endl;
    
    // Test with list
    std::list<int> lst;
    lst.push_back(10);
    lst.push_back(20);
    lst.push_back(30);
    lst.push_back(40);
    
    try {
        std::list<int>::iterator it = easyfind(lst, 20);
        std::cout << "Found value 20 in list" << std::endl;
        std::cout << "Value: " << *it << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    
    try {
        std::list<int>::iterator it = easyfind(lst, 100);
        (void)it;
        std::cout << "Found value 100 in list" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Exception when searching for 100: " << e.what() << std::endl;
    }
    
    std::cout << "\n=== Testing easyfind with std::deque ===" << std::endl;
    
    // Test with deque
    std::deque<int> deq;
    deq.push_back(5);
    deq.push_back(15);
    deq.push_back(25);
    
    try {
        std::deque<int>::iterator it = easyfind(deq, 15);
        std::cout << "Found value 15 in deque" << std::endl;
        std::cout << "Value: " << *it << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    
    std::cout << "\n=== Testing easyfind with const container ===" << std::endl;
    
    // Test with const container
    const std::vector<int> const_vec(vec);
    try {
        std::vector<int>::const_iterator it = easyfind(const_vec, 1);
        std::cout << "Found value 1 in const vector" << std::endl;
        std::cout << "Value: " << *it << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    
    std::cout << "\n=== Testing easyfind with empty container ===" << std::endl;
    
    // Test with empty container
    std::vector<int> empty_vec;
    try {
        std::vector<int>::iterator it = easyfind(empty_vec, 1);
        (void)it;
        std::cout << "Found value 1 in empty vector" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Exception when searching in empty container: " << e.what() << std::endl;
    }
    
    return 0;
}

/*

std::vector<int> vec;        // ✅ STL vector container
std::list<int> lst;          // ✅ STL list container  
std::deque<int> deq;         // ✅ STL deque container
const std::vector<int> const_vec(vec);  // ✅ const container


1. std::vector<int> vec
What it is: Dynamic array that can grow/shrink at runtime

Memory Layout:
vec: [1][2][3][4][5]  // Contiguous memory (like regular array)
     ↑              ↑
   begin()        end()
How it's utilized in our code:
std::vector<int> vec;
vec.push_back(1);     // Add to end: [1]
vec.push_back(2);     // Add to end: [1][2] 
vec.push_back(3);     // Add to end: [1][2][3]
vec.push_back(4);     // Add to end: [1][2][3][4]
vec.push_back(5);     // Add to end: [1][2][3][4][5]

// Iterator arithmetic works (random access)
std::cout << (it - vec.begin()) << std::endl;  // Calculate position

Key Features:
✅ Random access - vec[index] in O(1)
✅ Contiguous memory - cache-friendly
✅ Dynamic resizing - grows as needed
✅ Iterator arithmetic - can calculate distance


2. std::list<int> lst
What it is: Doubly-linked list

Memory Layout:
lst: [10] <-> [20] <-> [30] <-> [40]
     ↑                          ↑
   begin()                    end()
How it's utilized in our code:
std::list<int> lst;
lst.push_back(10);    // Add node: [10]
lst.push_back(20);    // Add node: [10] <-> [20]
lst.push_back(30);    // Add node: [10] <-> [20] <-> [30]
lst.push_back(40);    // Add node: [10] <-> [20] <-> [30] <-> [40]

// No iterator arithmetic possible
// std::cout << (it - lst.begin());  // ❌ Won't compile!

Key Features:
✅ Efficient insertion/deletion anywhere in O(1)
✅ No reallocation - elements stay in same memory location
❌ No random access - must traverse from beginning
❌ No iterator arithmetic - can only increment/decrement


3. std::deque<int> deq
What it is: Double-ended queue (pronounced "deck")

Memory Layout:
deq: [5][15][25]  // Segments of contiguous memory
     ↑         ↑
   begin()   end()
How it's utilized in our code:
std::deque<int> deq;
deq.push_back(5);     // Add to back: [5]
deq.push_back(15);    // Add to back: [5][15]
deq.push_back(25);    // Add to back: [5][15][25]

// Could also use:
// deq.push_front(0);  // Add to front: [0][5][15][25]

Key Features:
✅ Random access - deq[index] in O(1)
✅ Efficient front/back insertion - O(1) at both ends
✅ Iterator arithmetic - supports distance calculations
⚠️ Segmented memory - not as cache-friendly as vector


4. const std::vector<int> const_vec(vec)
What it is: Immutable copy of the original vector

How it's utilized in our code:
const std::vector<int> const_vec(vec);  // Copy constructor
// const_vec now contains: [1][2][3][4][5]

// Only read-only operations allowed:
std::vector<int>::const_iterator it = easyfind(const_vec, 1);
std::cout << *it;         // ✅ Can read
// *it = 42;              // ❌ Compile error - can't modify
// const_vec.push_back(6); // ❌ Compile error - can't modify
*/