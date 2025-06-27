#include "BitcoinExchange.hpp"
#include <iostream>

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "Error: could not open file." << std::endl;
        return 1;
    }
    
    BitcoinExchange exchange;
    
    try {
        // Load the database (data.csv should be in the same directory)
        exchange.loadDatabase("data.csv");
        
        // Process the input file
        exchange.processInputFile(argv[1]);
        
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}