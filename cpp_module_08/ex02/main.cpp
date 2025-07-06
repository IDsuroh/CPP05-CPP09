#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <iterator>
#include <stack>
#include <string>
#include "MutantStack.hpp"

// Function object for C++98 compatibility (replaces lambda) = called a functor a UnaryPredicate
struct GreaterThan20 {
	bool operator()(int n) const {
		return n > 20;
    }
};

// Exact test from exercise description
void exerciseTest() {
    std::cout << "=== Exercise Test (MutantStack) ===" << std::endl;
    
    MutantStack<int> mstack;
    mstack.push(5);
    mstack.push(17);
    
    std::cout << mstack.top() << std::endl << std::endl;
    mstack.pop();
    std::cout << "Stack size after pop: ";
    std::cout << mstack.size() << std::endl << std::endl;
    
    mstack.push(3);
    mstack.push(5);
    mstack.push(737);
    mstack.push(0);
    
    MutantStack<int>::iterator it = mstack.begin();
    MutantStack<int>::iterator ite = mstack.end();
    
    ++it;
    --it;
    while (it != ite)
    {
        std::cout << *it << std::endl;
        ++it;
    }
    
    std::stack<int> s(mstack);  // Test conversion to std::stack just to prove my copy constructor works well
    std::cout << "Converted to std::stack, size: " << s.size() << std::endl;
}

// Comparison test with std::list (should produce same output)
void listComparisonTest() {
    std::cout << "\n=== std::list Comparison Test ===" << std::endl;
    
    std::list<int> lst;
    lst.push_back(5);
    lst.push_back(17);
    
    std::cout << lst.back() << std::endl << std::endl;  // equivalent to top()
    lst.pop_back();
    std::cout << "Stack size after pop_back: ";         // equivalent to pop()
    std::cout << lst.size() << std::endl << std::endl;
    
    lst.push_back(3);
    lst.push_back(5);
    lst.push_back(737);
    lst.push_back(0);
    
    std::list<int>::iterator it = lst.begin();
    std::list<int>::iterator ite = lst.end();
    
    ++it;
    --it;
    while (it != ite)
    {
        std::cout << *it << std::endl;
        ++it;
    }
}

void testBasicFunctionality() {
    std::cout << "\n=== Basic Stack Functionality Test ===" << std::endl;
    
    MutantStack<int> mstack;
    
    // Test basic stack operations
    mstack.push(5);
    mstack.push(17);
    
    std::cout << "Top element: " << mstack.top() << std::endl; // Should be 17
    std::cout << "Stack size: " << mstack.size() << std::endl; // Should be 2
    
    mstack.pop();
    std::cout << "After pop, size: " << mstack.size() << std::endl; // Should be 1
    std::cout << "Top element: " << mstack.top() << std::endl; // Should be 5
    
    mstack.push(3);
    mstack.push(5);
    mstack.push(737);
    mstack.push(0);
    
    std::cout << "Final size: " << mstack.size() << std::endl; // Should be 5
}

void testIterators() {
    std::cout << "\n=== Iterator Test ===" << std::endl;
    
    MutantStack<int> mstack;
    
    // Add elements
    for (int i = 1; i <= 10; ++i) {
        mstack.push(i * 10);
    }
    
    std::cout << "Stack contents (forward iteration): ";
    for (MutantStack<int>::iterator it = mstack.begin(); it != mstack.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Stack contents (reverse iteration): ";
    for (MutantStack<int>::reverse_iterator it = mstack.rbegin(); it != mstack.rend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

void testWithSTLAlgorithms() {
    std::cout << "\n=== STL Algorithms Test ===" << std::endl;
    
    MutantStack<int> mstack;
    std::cout << "Adding elements to MutantStack..." << std::endl;
    
    // Add some numbers
    int numbers[] = {42, 8, 15, 23, 4, 16, 34, 7};
    for (int i = 0; i < 8; ++i) {
        mstack.push(numbers[i]);
    }
    
    std::cout << "Original stack: ";
    for (MutantStack<int>::iterator it = mstack.begin(); it != mstack.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // Find an element
    MutantStack<int>::iterator found = std::find(mstack.begin(), mstack.end(), 15);
    if (found != mstack.end()) {
        std::cout
		<< "Found element 15 at position: " << std::distance(mstack.begin(), found)
		<< std::endl;
    }

    // Count elements greater than 20 using function object
    int count = std::count_if(mstack.begin(), mstack.end(), GreaterThan20());
    std::cout << "Elements greater than 20: " << count << std::endl;
    
    // Find maximum element
    MutantStack<int>::iterator max_it = std::max_element(mstack.begin(), mstack.end());
    std::cout << "Maximum element: " << *max_it << std::endl;
}

void testConstIterators() {
    std::cout << "\n=== Const Iterator Test ===" << std::endl;
    
    MutantStack<int> mstack;
    for (int i = 1; i <= 5; ++i) {
        mstack.push(i * 100);
    }
    
    const MutantStack<int>& const_ref = mstack;
    
    std::cout << "Const iteration: ";
    for (MutantStack<int>::const_iterator it = const_ref.begin(); it != const_ref.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

void testDifferentContainers() {
    std::cout << "\n=== Different Container Test ===" << std::endl;
    
    // MutantStack with vector as underlying container
    MutantStack<std::string, std::vector<std::string> > vectorStack;
    vectorStack.push("Hello");
    vectorStack.push("World");
    vectorStack.push("MutantStack");
    
    std::cout << "Vector-based MutantStack: ";
    for (MutantStack<std::string, std::vector<std::string> >::iterator it = vectorStack.begin(); 
         it != vectorStack.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // MutantStack with list as underlying container
    MutantStack<int, std::list<int> > listStack;
    listStack.push(100);
    listStack.push(200);
    listStack.push(300);
    
    std::cout << "List-based MutantStack: ";
    for (MutantStack<int, std::list<int> >::iterator it = listStack.begin(); 
         it != listStack.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

void testCopyAndAssignment() {
    std::cout << "\n=== Copy and Assignment Test ===" << std::endl;
    
    MutantStack<int> original;
    original.push(1);
    original.push(2);
    original.push(3);
    
    // Test copy constructor
    MutantStack<int> copied(original);
    std::cout << "Copied stack: ";
    for (MutantStack<int>::iterator it = copied.begin(); it != copied.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // Test assignment operator
    MutantStack<int> assigned;
    assigned = original;
    std::cout << "Assigned stack: ";
    for (MutantStack<int>::iterator it = assigned.begin(); it != assigned.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // Modify original and check independence
    original.push(4);
    std::cout << "\nAfter modifying original ->" << std::endl;
    std::cout << "Original size: " << original.size() << std::endl;
    std::cout << "Copied size: " << copied.size() << std::endl;
    std::cout << "Assigned size: " << assigned.size() << std::endl;
}

void originalComparisonTest() {
    std::cout << "\n=== Original Comparison Test ===" << std::endl;
    
    // Subject test - compare with std::list
    std::cout << "MutantStack test ->" << std::endl;
    MutantStack<int> mstack;
    mstack.push(5);
    mstack.push(17);
    mstack.pop();
    mstack.push(3);
    mstack.push(5);
    mstack.push(737);
    mstack.push(0);
    
    MutantStack<int>::iterator s_it = mstack.begin();
    MutantStack<int>::iterator s_ite = mstack.end();
    
    ++s_it;
    --s_it;
    
    std::cout << "MutantStack iteration: ";
    while (s_it != s_ite) {
        std::cout << *s_it << " ";
        ++s_it;
    }
    std::cout << std::endl;
    
    // Same test with std::list for comparison
    std::cout << "\nstd::list test ->" << std::endl;
    std::list<int> lst;
    lst.push_back(5);
    lst.push_back(17);
    lst.pop_back();
    lst.push_back(3);
    lst.push_back(5);
    lst.push_back(737);
    lst.push_back(0);
    
    std::list<int>::iterator l_it = lst.begin();
    std::list<int>::iterator l_ite = lst.end();
    
    ++l_it;
    --l_it;
    
    std::cout << "std::list iteration:   ";
    while (l_it != l_ite) {
        std::cout << *l_it << " ";
        ++l_it;
    }
    std::cout << std::endl;
    
    std::cout << "\n=> Both outputs should be identical!" << std::endl;
}

int main() {
    // Exercise-required tests first
    exerciseTest();
    listComparisonTest();
    
    // Comprehensive additional tests
    testBasicFunctionality();
    testIterators();
    testWithSTLAlgorithms();
    testConstIterators();
    testDifferentContainers();
    testCopyAndAssignment();
    originalComparisonTest();
    
    std::cout << "\n=== All Tests Completed ===" << std::endl;
    
    return 0;
}