#include <iostream>
#include "BitcoinExchange.hpp"

int main(int argc, char** argv) {
    if (argc != 2)  {
        std::cerr << "Error: Can't open file.\n";
        return 1;
    }

    try {
        BitcoinExchange exchange;
        exchange.loadDatabase("data.csv");
        exchange.processInputFile(argv[1]);
    } catch (const std::exception& e)   {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}