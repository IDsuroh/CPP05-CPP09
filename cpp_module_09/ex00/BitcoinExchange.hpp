#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cstdlib>
#include <cctype>

class BitcoinExchange {
private:
    std::map<std::string, float> _database;
    
    void processLine(const std::string& line);
    bool isValidValueString(const std::string& valueStr) const;
    std::string trim(const std::string& str) const;
    
public:
    BitcoinExchange();
    BitcoinExchange(const BitcoinExchange& other);
    BitcoinExchange& operator=(const BitcoinExchange& other);
    ~BitcoinExchange();
    
    void loadDatabase(const std::string& filename);
    void processInputFile(const std::string& filename);
    float getExchangeRate(const std::string& date) const;
    bool isValidDate(const std::string& date) const;
    bool isValidValue(float value) const;
};

#endif