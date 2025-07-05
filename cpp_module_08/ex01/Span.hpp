#ifndef SPAN_HPP
#define SPAN_HPP

#include <vector>
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <climits>

class Span {
private:
    unsigned int _maxSize;
    std::vector<int> _numbers;

public:
    Span(unsigned int N);
    Span(const Span& other);
    Span& operator=(const Span& other);
    ~Span();
    
    void addNumber(int number);
    
    // Declaration INSIDE class - NO Span:: qualifier
    template<typename Iterator>
    void addNumber(Iterator begin, Iterator end);
    
    unsigned int shortestSpan() const;
    unsigned int longestSpan() const;
    
    unsigned int size() const;
    unsigned int maxSize() const;
    
    class SpanFullException : public std::exception {
    public:
        virtual const char* what() const throw();
    };
    
    class NoSpanException : public std::exception {
    public:
        virtual const char* what() const throw();
    };
};

// Definition OUTSIDE class - WITH Span:: qualifier
template<typename Iterator>
void Span::addNumber(Iterator begin, Iterator end) {
    typename std::iterator_traits<Iterator>::difference_type distance
        = std::distance(begin, end);
    if (_numbers.size() + static_cast<size_t>(distance) > _maxSize) {
        throw SpanFullException();
    }
    _numbers.reserve(_numbers.size() + distance);
    std::copy(begin, end, std::back_inserter(_numbers));
}

#endif

/*


---Why Two Versions of addNumber()?---
The two versions provide different interfaces for adding elements:

Version 1: Single Element
	void addNumber(int number);
Use case: Adding one number at a time
	Span sp(5);
	sp.addNumber(10);
	sp.addNumber(20);
	sp.addNumber(30);

Version 2: Range of Elements (Template)
	template<typename Iterator>
	void addNumber(Iterator begin, Iterator end);
Use case: Adding multiple elements from a range (e.g., another container)
	Span sp(1000);

	// From vector
	std::vector<int> data = {1, 2, 3, 4, 5};
	sp.addNumber(data.begin(), data.end());

	// From array
	int arr[] = {10, 20, 30};
	sp.addNumber(arr, arr + 3);

	// From list
	std::list<int> lst = {100, 200, 300};
	sp.addNumber(lst.begin(), lst.end());

---Comparison of Performance:---
// Slow way - multiple function calls
for (int i = 0; i < 10000; ++i) {
    sp.addNumber(i);  // 10,000 function calls + 10,000 bound checks
}

// Fast way - single function call
std::vector<int> data(10000);
std::iota(data.begin(), data.end(), 0);  // Fill with 0,1,2,...,9999
sp.addNumber(data.begin(), data.end());  // 1 function call + 1 bound check

--------------------------------------------------------------------------------------
manual version
template<typename Iterator>
    while (begin != end) {
        if (_numbers.size() >= _maxSize) {
            throw SpanFullException();
        }
        _numbers.push_back(*begin);
        ++begin;
    }
}


=====std::iterator_traits<Iterator>

From: #include <iterator>
What: Gets information about the iterator type
Purpose: Provides difference_type (usually ptrdiff_t or int)

=====std::distance(begin, end)

From: #include <iterator>

=====_numbers.reserve(_numbers.size() + distance);

From: std::vector member function (#include <vector>)
What: Pre-allocates memory to avoid multiple reallocations
Why: Performance optimization

=====std::copy(begin, end, std::back_inserter(_numbers));

std::copy

From: #include <algorithm>
What: Copies elements from source range to destination

std::back_inserter(_numbers)

From: #include <iterator>
What: Creates an iterator that calls push_back() on each assignment
Why: Allows std::copy to add elements to the end of vector


Header Mapping
Component	            Header	    Purpose
std::iterator_traits	<iterator>	Iterator type information
std::distance	        <iterator>	Calculate iterator distance
std::back_inserter	    <iterator>	Output iterator adapter
std::copy	            <algorithm>	Copy algorithm
std::vector	            <vector>	Container and reserve()

*/
