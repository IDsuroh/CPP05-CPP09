#include <algorithm>    // std::lower_bound, std::swap
#include <ctime>        // clock(), CLOCKS_PER_SEC
#include <stdexcept>    // std::runtime_error
#include "PmergeMe.hpp"

static double   elapsed_us(clock_t start, clock_t end)  {
    return ((double)(end - start) * 1e6 / CLOCKS_PER_SEC);
}

PmergeMe::PmergeMe()
{}

PmergeMe::PmergeMe(const PmergeMe& other)   {
    (void)other;
}

PmergeMe&   PmergeMe::operator=(const PmergeMe& other)  {
    (void)other;
    return *this;
}

PmergeMe::~PmergeMe()
{}

double  PmergeMe::sortVector(std::vector<int>& sequence)    {
    clock_t t0 = clock();
    mergeInsertVector(sequence);
    clock_t t1 = clock();
    return (elapsed_us(t0, t1));
}

double  PmergeMe::sortDeque(std::deque<int>& sequence)    {
    clock_t t0 = clock();
    mergeInsertDeque(sequence);
    clock_t t1 = clock();
    return (elapsed_us(t0, t1));
}

void    PmergeMe::mergeInsertVector(std::vector<int>& seq)  {

    int n = seq.size();
    
    if (n <= 1)
        return;
    
    if (n == 2) {
        if (seq[0] >seq[1])
            std::swap(seq[0], seq[1]);
        return;
    }

    int numPairs = n / 2;
    std::vector<int>    firsts;
    std::vector<int>    seconds;
    firsts.reserve(numPairs + (n % 2));
    seconds.reserve(numPairs);

    for (int i = 0; i < numPairs; ++i)  {
        int a = seq[2 * i], b = seq[2 * i + 1];
        if (a <= b) {
            firsts.push_back(a);
            seconds.push_back(b);
        } else  {
            firsts.push_back(b);
            seconds.push_back(a);
        }
    }

    if (n % 2 == 1)
        firsts.push_back(seq[n - 1]);

    mergeInsertVector(firsts);

    for (size_t i = 0; i < seconds.size(); ++i) {
        int value = seconds[i];
        std::vector<int>::iterator  pos
            = std::lower_bound(firsts.begin(), firsts.end(), value);
        firsts.insert(pos, value);
    }

    for (int i = 0; i < n; ++i)
        seq[i] = firsts[i];
}

void    PmergeMe::mergeInsertDeque(std::deque<int>& seq)    {

    int n = seq.size();

    if (n <= 1)
        return;

    if (n == 2) {
        if (seq[0] > seq[1])
            std::swap(seq[0], seq[1]);
        return;
    }

    int numPairs = n / 2;
    std::deque<int> firsts;
    std::deque<int> seconds;

    for (int i = 0; i < numPairs; ++i)  {
        int a = seq[2 * i], b = seq[2 * i + 1];
        if (a <= b) {
            firsts.push_back(a);
            seconds.push_back(b);
        } else  {
            firsts.push_back(b);
            seconds.push_back(a);
        }
    }

    if (n % 2 == 1)
        firsts.push_back(seq[n - 1]);

    mergeInsertDeque(firsts);

    for (int i = 0; i < numPairs; ++i)  {
        int value = seconds[i];
        std::deque<int>::iterator   pos
            = std::lower_bound(firsts.begin(), firsts.end(), value);
        firsts.insert(pos, value);
    }

    for (int i = 0; i < n; ++i)
        seq[i] = firsts[i];
}