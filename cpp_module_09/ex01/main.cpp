#include <iostream>
#include "RPN.hpp"

int main(int argc, char** argv) {
    if (argc != 2)  {
        std::cerr << "Error\n";
        return 1;
    }

    try {
        RPN calculation;
        int result = calculation.evaluate(argv[1]);
        std::cout
            << result << std::endl;
    } catch (const std::exception&) {
        std::cerr << "Error\n";
        return 1;
    }

    return 0;
}