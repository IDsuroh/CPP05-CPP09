#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

BitcoinExchange::BitcoinExchange()
{}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
    :   _database(other._database)
    {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
    if (this != &other) {
        _database = other._database;
    }
    return *this;
}

BitcoinExchange::~BitcoinExchange()
{}

void BitcoinExchange::loadDatabase(const std::string& filename) {
    std::ifstream file(filename.c_str());
    if (!file.is_open()) {
        throw std::runtime_error("Error: could not open database file.");
    }
    
    std::string line;
    // Skip header line
    if (std::getline(file, line)) {
        // Header line: "date,exchange_rate"
    }
    
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        
        size_t commaPos = line.find(',');
        if (commaPos == std::string::npos) continue;
        
        std::string date = line.substr(0, commaPos);
        std::string rateStr = line.substr(commaPos + 1);
        
        // Trim whitespace
        date = trim(date);
        rateStr = trim(rateStr);
        
        if (isValidDate(date)) {
            float rate = std::atof(rateStr.c_str());
            _database[date] = rate;
        }
    }
    
    file.close();
}

void BitcoinExchange::processInputFile(const std::string& filename) {
    std::ifstream file(filename.c_str());
    if (!file.is_open()) {
        std::cout << "Error: could not open file." << std::endl;
        return;
    }
    
    std::string line;
    // Skip header line if it exists
    if (std::getline(file, line)) {
        if (line != "date | value") {
            // Process this line if it's not a header
            processLine(line);
        }
    }
    
    while (std::getline(file, line)) {
        if (!line.empty()) {
            processLine(line);
        }
    }
    
    file.close();
}

void BitcoinExchange::processLine(const std::string& line) {
    size_t pipePos = line.find(" | ");
    if (pipePos == std::string::npos) {
        std::cout << "Error: bad input => " << line << std::endl;
        return;
    }
    
    std::string date = line.substr(0, pipePos);
    std::string valueStr = line.substr(pipePos + 3);
    
    // Trim whitespace
    date = trim(date);
    valueStr = trim(valueStr);
    
    if (!isValidDate(date)) {
        std::cout << "Error: bad input => " << date << std::endl;
        return;
    }
    
    if (!isValidValueString(valueStr)) {
        std::cout << "Error: bad input => " << valueStr << std::endl;
        return;
    }
    
    float value = std::atof(valueStr.c_str());
    
    if (!isValidValue(value)) {
        if (value < 0) {
            std::cout << "Error: not a positive number." << std::endl;
        } else {
            std::cout << "Error: too large a number." << std::endl;
        }
        return;
    }

    float rate = getExchangeRate(date);
    float result = value * rate;
    if (result == -0)
        result = 0;
    
    std::cout << date << " => " << value << " = " << result << std::endl;
}

float BitcoinExchange::getExchangeRate(const std::string& date) const {
    // Try to find exact date
    std::map<std::string, float>::const_iterator it = _database.find(date);
    if (it != _database.end()) {
        return it->second;
    }
    
    // Find closest lower date
    it = _database.lower_bound(date);
    if (it == _database.begin()) {
        // If date is before all dates in database, use first date
        return _database.begin()->second;
    }
    
    // Go to previous date (lower date)
    --it;
    return it->second;
}

bool BitcoinExchange::isValidDate(const std::string& date) const {
    if (date.length() != 10)
        return false;
    if (date[4] != '-' || date[7] != '-')
        return false;
    
    // Extract year, month, day
    std::string yearStr = date.substr(0, 4);
    std::string monthStr = date.substr(5, 2);
    std::string dayStr = date.substr(8, 2);
    
    // Check if all characters are digits
    for (size_t i = 0; i < yearStr.length(); ++i) {
        if (!std::isdigit(yearStr[i]))
            return false;
    }
    for (size_t i = 0; i < monthStr.length(); ++i) {
        if (!std::isdigit(monthStr[i]))
            return false;
    }
    for (size_t i = 0; i < dayStr.length(); ++i) {
        if (!std::isdigit(dayStr[i]))
            return false;
    }
    
    int year = std::atoi(yearStr.c_str());
    int month = std::atoi(monthStr.c_str());
    int day = std::atoi(dayStr.c_str());
    
    // Basic range checks
    if (year < 1000 || year > 9999)
        return false;
    if (month < 1 || month > 12)
        return false;
    if (day < 1 || day > 31)
        return false;
    
    // More specific day checks
    if (month == 2) {
        bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (day > (isLeap ? 29 : 28))
            return false;
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        if (day > 30)
            return false;
    }
    
    return true;
}

bool BitcoinExchange::isValidValue(float value) const {
    return value >= 0 && value <= 1000;
}

bool BitcoinExchange::isValidValueString(const std::string& valueStr) const {
    if (valueStr.empty())
        return false;
    
    size_t start = 0;
    if (valueStr[0] == '-' || valueStr[0] == '+') {
        start = 1;
    }
    
    bool hasDot = false;
    for (size_t i = start; i < valueStr.length(); ++i) {
        if (valueStr[i] == '.') {
            if (hasDot)
                return false; // Multiple dots
            hasDot = true;
        } else if (!std::isdigit(valueStr[i])) {
            return false;
        }
    }
    
    return start < valueStr.length(); // Make sure there's at least one digit
}

std::string BitcoinExchange::trim(const std::string& str) const {
    size_t start = str.find_first_not_of(" \t\r\n");
    if (start == std::string::npos)
        return "";
    
    size_t end = str.find_last_not_of(" \t\r\n");
    return str.substr(start, end - start + 1);
}