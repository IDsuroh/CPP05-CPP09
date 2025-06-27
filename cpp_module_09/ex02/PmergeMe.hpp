#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <sys/time.h>
#include <sstream>
#include <stdexcept>
#include <cstdlib>

class PmergeMe {
private:
    std::vector<int> _vectorContainer;
    std::deque<int> _dequeContainer;
    
    // Vector implementation
    void fordJohnsonSortVector(std::vector<int>& container);
    void mergeInsertVector(std::vector<int>& container, int size);
    void insertionSortVector(std::vector<int>& container, int left, int right);
    
    // Deque implementation
    void fordJohnsonSortDeque(std::deque<int>& container);
    void mergeInsertDeque(std::deque<int>& container, int size);
    void insertionSortDeque(std::deque<int>& container, int left, int right);
    
    // Utility functions
    bool isValidNumber(const std::string& str) const;
    double getCurrentTime() const;
    void displayContainer(const std::vector<int>& container) const;
    void displayContainer(const std::deque<int>& container) const;
    
public:
    PmergeMe();
    PmergeMe(const PmergeMe& other);
    PmergeMe& operator=(const PmergeMe& other);
    ~PmergeMe();
    
    void parseArguments(char** argv, int argc);
    void sortAndCompare();
};

#endif