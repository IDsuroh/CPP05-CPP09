#include <iostream>
#include <vector>
#include <deque>
#include <cstdlib>
#include <iomanip>      // fixed, setprecision
#include "PmergeMe.hpp"

int main(int argc, char** argv) {
    if (argc < 2)   {
        std::cerr << "Error\n";
        return 1;
    }

    std::vector<int> vec;
    std::deque<int> deq;
    for (int i = 1; i < argc; ++i)  {
        if (argv[i][0] == '\0') {
            std::cerr << "Error\n";
        }
        int x = std::atoi(argv[i]);
        if (x <= 0) {
            std::cerr << "Error\n";
            return 1;
        }
        vec.push_back(x);
        deq.push_back(x);
    }

    std::cout << "Before:";
    for (size_t i = 0; i < vec.size(); ++i)
        std::cout << " " << vec[i];
    std::cout << std::endl;

    PmergeMe    sorter;
    double      tVec = sorter.sortVector(vec);
    double      tDeq = sorter.sortDeque(deq);

    std::cout << "After:";
    for (size_t i = 0; i < vec.size(); ++i)
        std::cout << " " << vec[i];
    std::cout << std::endl;

    std::cout
        << std::fixed << std::setprecision(5);

    std::cout
        << "Time to process a range of " << vec.size()
        << " elements with std::vector : " << tVec << " us\n"
        << "Time to process a range of " << deq.size()
        << " elements with std::deque : " << tDeq << " us\n";

    return 0;
}