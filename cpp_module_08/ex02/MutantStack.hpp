#ifndef MUTANTSTACK_HPP
#define MUTANTSTACK_HPP

#include <stack>
#include <deque>

// Declares that MutantStack is a class template parameterized by 2 types.
// T -> type of elements   Container -> the underlying container type.
template<typename T, typename Container = std::deque<T> >
class MutantStack : public std::stack<T, Container> {
public:
    // Type definitions for iterators
    typedef typename Container::iterator iterator;
    typedef typename Container::const_iterator const_iterator;
    typedef typename Container::reverse_iterator reverse_iterator;
    typedef typename Container::const_reverse_iterator const_reverse_iterator;

    MutantStack();
    MutantStack(const MutantStack& other);
    MutantStack& operator=(const MutantStack& other);
    ~MutantStack();

    // Iterator functions
    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
    
    reverse_iterator rbegin();
    reverse_iterator rend();
    const_reverse_iterator rbegin() const;
    const_reverse_iterator rend() const;
};

#include "MutantStack.tpp"

#endif

/*

1. What is a “stack”? What is std::stack?
How is it different from std::deque, std::vector, std::list?
    - A stack is a LIFO (last-in, first-out) data structure.
    - You can only add (push) items to the “top,”
        look at (top) the most recent item, or remove (pop) that top item.
    - Think of a stack of plates—only the top plate is ever accessible.

std::stack:
In C++, std::stack<T,Container> is a container adapter.
It doesn’t store elements itself, but wraps another container
(by default a std::deque<T>) and restricts its interface to the
three main operations—push(), pop(), and top()—plus size() and empty().

by default it uses deque<T> under the hood.
You could write std::stack<T,std::vector<T>> or
std::stack<T,std::list<T>> if you preferred those performance
characteristics, but you lose the ability to access elements except
through the LIFO interface.

*/