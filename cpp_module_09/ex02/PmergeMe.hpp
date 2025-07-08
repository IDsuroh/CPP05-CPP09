#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>

class PmergeMe  {
    public:
        PmergeMe();
        PmergeMe(const PmergeMe& other);
        PmergeMe& operator=(const PmergeMe& other);
        ~PmergeMe();

        double  sortVector(std::vector<int>& sequence);
        double  sortDeque(std::deque<int>& sequence);

    private:
        void    mergeInsertVector(std::vector<int>& seq);
        void    mergeInsertDeque(std::deque<int>& seq);
};

#endif