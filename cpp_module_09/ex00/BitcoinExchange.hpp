#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>          //-> to store date->rate pairs
#include <string>       //
#include <iostream>     //
#include <fstream>      //->for file I/O and string parsing
#include <sstream>      //
#include <stdexcept>
#include <cstdlib>
#include <cctype>

class BitcoinExchange   {
    
    private:
        std::map<std::string, float> _database;
    
    public:
        BitcoinExchange();
        BitcoinExchange(const std::string& dataFile);
        BitcoinExchange(const BitcoinExchange& other);
        BitcoinExchange& operator=(const BitcoinExchange& other);
        ~BitcoinExchange();

        void    loadDatabase(const std::string& filename);
        void    processInputFile(const std::string& inputFile) const;
    
    private:
        std::string trim(const std::string& str) const;
        bool    isValidDate(const std::string& date) const;
};

#endif