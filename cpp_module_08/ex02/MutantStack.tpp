#ifndef MUTANTSTACK_TPP
#define MUTANTSTACK_TPP

#include "MutantStack.hpp"

// Default constructor
template<typename T, typename Container>
MutantStack<T, Container>::MutantStack() : std::stack<T, Container>() {}

// Copy constructor
template<typename T, typename Container>
MutantStack<T, Container>::MutantStack(const MutantStack& other) : std::stack<T, Container>(other) {}

// Assignment operator
template<typename T, typename Container>
MutantStack<T, Container>& MutantStack<T, Container>::operator=(const MutantStack& other) {
    if (this != &other) {
        std::stack<T, Container>::operator=(other);
    }
    return *this;
}

// Destructor
template<typename T, typename Container>
MutantStack<T, Container>::~MutantStack() {}

// Iterator implementations
template<typename T, typename Container>
typename MutantStack<T, Container>::iterator MutantStack<T, Container>::begin() {
    return this->c.begin();
}

template<typename T, typename Container>
typename MutantStack<T, Container>::iterator MutantStack<T, Container>::end() {
    return this->c.end();
}

template<typename T, typename Container>
typename MutantStack<T, Container>::const_iterator MutantStack<T, Container>::begin() const {
    return this->c.begin();
}

template<typename T, typename Container>
typename MutantStack<T, Container>::const_iterator MutantStack<T, Container>::end() const {
    return this->c.end();
}

template<typename T, typename Container>
typename MutantStack<T, Container>::reverse_iterator MutantStack<T, Container>::rbegin() {
    return this->c.rbegin();
}

template<typename T, typename Container>
typename MutantStack<T, Container>::reverse_iterator MutantStack<T, Container>::rend() {
    return this->c.rend();
}

template<typename T, typename Container>
typename MutantStack<T, Container>::const_reverse_iterator MutantStack<T, Container>::rbegin() const {
    return this->c.rbegin();
}

template<typename T, typename Container>
typename MutantStack<T, Container>::const_reverse_iterator MutantStack<T, Container>::rend() const {
    return this->c.rend();
}

/*

you’re defining the begin() function of MutantStack<T,Container>,
and that function returns an object of the nested type iterator.

*/
#endif