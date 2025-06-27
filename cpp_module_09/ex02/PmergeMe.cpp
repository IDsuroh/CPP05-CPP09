#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe& other) 
    : _vectorContainer(other._vectorContainer), _dequeContainer(other._dequeContainer) {}

PmergeMe& PmergeMe::operator=(const PmergeMe& other) {
    if (this != &other) {
        _vectorContainer = other._vectorContainer;
        _dequeContainer = other._dequeContainer;
    }
    return *this;
}

PmergeMe::~PmergeMe() {}

void PmergeMe::parseArguments(char** argv, int argc) {
    for (int i = 1; i < argc; ++i) {
        if (!isValidNumber(argv[i])) {
            throw std::runtime_error("Error");
        }
        
        int num = std::atoi(argv[i]);
        if (num <= 0) {
            throw std::runtime_error("Error");
        }
        
        _vectorContainer.push_back(num);
        _dequeContainer.push_back(num);
    }
    
    if (_vectorContainer.empty()) {
        throw std::runtime_error("Error");
    }
}

void PmergeMe::sortAndCompare() {
    // Display original sequence
    std::cout << "Before: ";
    displayContainer(_vectorContainer);
    
    // Sort with vector and measure time
    std::vector<int> vectorCopy = _vectorContainer;
    double startTime = getCurrentTime();
    fordJohnsonSortVector(vectorCopy);
    double vectorTime = getCurrentTime() - startTime;
    
    // Sort with deque and measure time
    std::deque<int> dequeCopy = _dequeContainer;
    startTime = getCurrentTime();
    fordJohnsonSortDeque(dequeCopy);
    double dequeTime = getCurrentTime() - startTime;
    
    // Display sorted sequence
    std::cout << "After:  ";
    displayContainer(vectorCopy);
    
    // Display timing information
    std::cout << "Time to process a range of " << _vectorContainer.size() 
              << " elements with std::vector : " << vectorTime << " us" << std::endl;
    std::cout << "Time to process a range of " << _dequeContainer.size() 
              << " elements with std::deque  : " << dequeTime << " us" << std::endl;
}

void PmergeMe::fordJohnsonSortVector(std::vector<int>& container) {
    if (container.size() <= 1) return;
    mergeInsertVector(container, container.size());
}

void PmergeMe::mergeInsertVector(std::vector<int>& container, int size) {
    if (size <= 15) {
        insertionSortVector(container, 0, size - 1);
        return;
    }
    
    // Create pairs and sort them
    std::vector<std::pair<int, int> > pairs;
    int unpaired = -1;
    
    for (int i = 0; i < size - 1; i += 2) {
        if (container[i] > container[i + 1]) {
            pairs.push_back(std::make_pair(container[i], container[i + 1]));
        } else {
            pairs.push_back(std::make_pair(container[i + 1], container[i]));
        }
    }
    
    if (size % 2 == 1) {
        unpaired = container[size - 1];
    }
    
    // Recursively sort the larger elements
    std::vector<int> larger;
    for (size_t i = 0; i < pairs.size(); ++i) {
        larger.push_back(pairs[i].first);
    }
    
    if (larger.size() > 1) {
        mergeInsertVector(larger, larger.size());
    }
    
    // Insert smaller elements using binary search
    std::vector<int> result = larger;
    
    for (size_t i = 0; i < pairs.size(); ++i) {
        int toInsert = pairs[i].second;
        std::vector<int>::iterator pos = std::lower_bound(result.begin(), result.end(), toInsert);
        result.insert(pos, toInsert);
    }
    
    if (unpaired != -1) {
        std::vector<int>::iterator pos = std::lower_bound(result.begin(), result.end(), unpaired);
        result.insert(pos, unpaired);
    }
    
    container = result;
}

void PmergeMe::insertionSortVector(std::vector<int>& container, int left, int right) {
    for (int i = left + 1; i <= right; ++i) {
        int key = container[i];
        int j = i - 1;
        
        while (j >= left && container[j] > key) {
            container[j + 1] = container[j];
            --j;
        }
        container[j + 1] = key;
    }
}

void PmergeMe::fordJohnsonSortDeque(std::deque<int>& container) {
    if (container.size() <= 1) return;
    mergeInsertDeque(container, container.size());
}

void PmergeMe::mergeInsertDeque(std::deque<int>& container, int size) {
    if (size <= 15) {
        insertionSortDeque(container, 0, size - 1);
        return;
    }
    
    // Create pairs and sort them
    std::deque<std::pair<int, int> > pairs;
    int unpaired = -1;
    
    for (int i = 0; i < size - 1; i += 2) {
        if (container[i] > container[i + 1]) {
            pairs.push_back(std::make_pair(container[i], container[i + 1]));
        } else {
            pairs.push_back(std::make_pair(container[i + 1], container[i]));
        }
    }
    
    if (size % 2 == 1) {
        unpaired = container[size - 1];
    }
    
    // Recursively sort the larger elements
    std::deque<int> larger;
    for (size_t i = 0; i < pairs.size(); ++i) {
        larger.push_back(pairs[i].first);
    }
    
    if (larger.size() > 1) {
        mergeInsertDeque(larger, larger.size());
    }
    
    // Insert smaller elements using binary search
    std::deque<int> result = larger;
    
    for (size_t i = 0; i < pairs.size(); ++i) {
        int toInsert = pairs[i].second;
        std::deque<int>::iterator pos = std::lower_bound(result.begin(), result.end(), toInsert);
        result.insert(pos, toInsert);
    }
    
    if (unpaired != -1) {
        std::deque<int>::iterator pos = std::lower_bound(result.begin(), result.end(), unpaired);
        result.insert(pos, unpaired);
    }
    
    container = result;
}

void PmergeMe::insertionSortDeque(std::deque<int>& container, int left, int right) {
    for (int i = left + 1; i <= right; ++i) {
        int key = container[i];
        int j = i - 1;
        
        while (j >= left && container[j] > key) {
            container[j + 1] = container[j];
            --j;
        }
        container[j + 1] = key;
    }
}

bool PmergeMe::isValidNumber(const std::string& str) const {
    if (str.empty()) return false;
    
    for (size_t i = 0; i < str.length(); ++i) {
        if (!std::isdigit(str[i])) {
            return false;
        }
    }
    
    // Check for overflow
    long num = std::atol(str.c_str());
    if (num > 2147483647 || num < 0) {
        return false;
    }
    
    return true;
}

double PmergeMe::getCurrentTime() const {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000.0 + tv.tv_usec;
}

void PmergeMe::displayContainer(const std::vector<int>& container) const {
    for (size_t i = 0; i < container.size(); ++i) {
        std::cout << container[i];
        if (i < container.size() - 1) std::cout << " ";
    }
    std::cout << std::endl;
}

void PmergeMe::displayContainer(const std::deque<int>& container) const {
    for (size_t i = 0; i < container.size(); ++i) {
        std::cout << container[i];
        if (i < container.size() - 1) std::cout << " ";
    }
    std::cout << std::endl;
}