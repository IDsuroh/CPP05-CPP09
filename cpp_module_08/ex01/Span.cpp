#include "Span.hpp"

Span::Span(unsigned int N)
    :   _maxSize(N) {
    _numbers.reserve(N);
}

/*	*** IMPORTANT NOTE ***

	we are using reserve() to directly place elements.
	What does this mean?
	- because std::vector Memory works like this:

	std::vector<int> vec;  // Capacity: 0, Size: 0

vec.push_back(1);      // Capacity: 1, Size: 1 [1]
vec.push_back(2);      // Capacity: 2, Size: 2 [1][2] - REALLOCATION!
vec.push_back(3);      // Capacity: 4, Size: 3 [1][2][3][_] - REALLOCATION!
vec.push_back(4);      // Capacity: 4, Size: 4 [1][2][3][4]
vec.push_back(5);      // Capacity: 8, Size: 5 [1][2][3][4][5][_][_][_] - REALLOCATION!

Span span(1000);
for (int i = 0; i < 1000; ++i) {
    span.addNumber(i);  // Multiple reallocations as vector grows
}
// Reallocations happen at: 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024

Span::Span(unsigned int N) : _maxSize(N) {
    _numbers.reserve(N);  // Allocate memory for N elements upfront
}

// Now adding elements is just placing them in pre-allocated space
for (int i = 0; i < 1000; ++i) {
    span.addNumber(i);  // No reallocations! Just direct placement
}

*/

Span::Span(const Span& other)
    :   _maxSize(other._maxSize), _numbers(other._numbers) {}

Span& Span::operator=(const Span& other) {
    if (this != &other) {
        _maxSize = other._maxSize;
        _numbers = other._numbers;
    }
    return *this;
}

Span::~Span() {}

void Span::addNumber(int number) {
    if (_numbers.size() >= _maxSize) {
        throw SpanFullException();
    }
    _numbers.push_back(number);
}

unsigned int Span::shortestSpan() const {
    if (_numbers.size() < 2) {
        throw NoSpanException();
    }
    std::vector<int> sorted = _numbers;
    std::sort(sorted.begin(), sorted.end());
    unsigned int minSpan = UINT_MAX;
    for (size_t i = 1; i < sorted.size(); ++i) {
        unsigned int span = sorted[i] - sorted[i - 1];
        if (span < minSpan) {
            minSpan = span;
        }
    }
    return minSpan;
}

unsigned int Span::longestSpan() const {
    if (_numbers.size() < 2) {
        throw NoSpanException();
    }
    std::vector<int>::const_iterator minIt
        = std::min_element(_numbers.begin(), _numbers.end());
    std::vector<int>::const_iterator maxIt
        = std::max_element(_numbers.begin(), _numbers.end());
    return *maxIt - *minIt;
}

unsigned int Span::size() const {
    return _numbers.size();
}

unsigned int Span::maxSize() const {
    return _maxSize;
}

// Exception implementations
const char* Span::SpanFullException::what() const throw() {
    return "Span is full, cannot add more numbers";
}

const char* Span::NoSpanException::what() const throw() {
    return "Cannot find span with less than 2 numbers";
}
