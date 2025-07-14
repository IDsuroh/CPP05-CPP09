#include "BitcoinExchange.hpp"

<<<<<<< HEAD
BitcoinExchange::BitcoinExchange()
=======
BitcoinExchange::BitcoinExchange() 
>>>>>>> 7abff59c0674373a6c82cb69d95588c48e0b5a70
{}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
    :   _database(other._database)
<<<<<<< HEAD
    {}
=======
{}
>>>>>>> 7abff59c0674373a6c82cb69d95588c48e0b5a70

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)   {
    if (this != &other)
        _database = other._database;
    return *this;
}

BitcoinExchange::~BitcoinExchange()
{}
<<<<<<< HEAD
=======

void    BitcoinExchange::loadDatabase(const std::string& filename)  {
    std::ifstream   file(filename.c_str());
    if (!file.is_open())
        throw std::runtime_error("Error:could not open database file.");
>>>>>>> 7abff59c0674373a6c82cb69d95588c48e0b5a70

    std::string line;
    std::getline(file, line);

    while (std::getline(file, line))    {
        if (line.empty())
            continue;
        size_t  commaPos = line.find(',');
        if (commaPos == std::string::npos)
            continue;

        std::string dateStr = line.substr(0, commaPos);
        std::string rateStr = line.substr(commaPos + 1);

        float   rate = std::atof(rateStr.c_str());
        if (!isValidDate(dateStr) || rate < 0.0f)
            continue;
        
        _database[dateStr] = rate;
    }
    file.close();
}

void    BitcoinExchange::processInputFile(const std::string& filename) const    {
    std::ifstream   infile(filename.c_str());
    if (!infile.is_open())  {
        std::cerr << "Error: could not open file.\n";
        return ;
    }

    std::string line;
    std::getline(infile, line);

    while (std::getline(infile, line)) {
        if (line.empty())
            continue;

        size_t  pipePos = line.find( " | ");
        if (pipePos == std::string::npos)   {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }

        std::string date = trim(line.substr(0,pipePos));
        std::string valueStr = trim(line.substr(pipePos + 3));

        if (!isValidDate(date)) {
            std::cerr << "Error: bad input => " << date << std::endl;
            continue;
        }

        if (!valueStr.empty() && valueStr[0] == '-') {
            std::cerr << "Error: not a positive number.\n";
            continue;
        }

        int dotCount = 0;
        for(std::size_t i = 0; i < valueStr.size(); ++i)    {
            if (valueStr[i] == '.')
                ++dotCount;
        }
        if (dotCount > 1)   {
            std::cerr << "Error: invalid format => " << valueStr << std::endl;
            continue;
        }

        if (valueStr.empty() || valueStr == ".")    {
            std::cerr << "Error: invalid format => " << valueStr << std::endl;
            continue;
        }
        
        bool    allGood = true;
        for (std::size_t    i = 0; i < valueStr.size(); ++i)    {
            char    c = valueStr[i];
            if (c != '.' && !std::isdigit(static_cast<unsigned char>(c)))   {
                allGood = false;
                break;
            }
        }
        if (!allGood)   {
            std::cerr << "Error: invalid number => " << valueStr << std::endl;
            continue ;
        }

        float   value = std::atof(valueStr.c_str());
        if (value > 1000.0f)    {
            std::cerr << "Error: too large a number.\n";
            continue;
        }

        std::map<std::string, float>::const_iterator it
            = _database.lower_bound(date);
        if (it == _database.end() || it->first != date) {
            if (it == _database.begin())    {
                std::cerr << "Error: date too early => " << date << std::endl;
                continue ; 
            }
            --it;
        }

        float   rate = it->second;
        std::cout
            << date << " => " << value << " = " << (value * rate) << std::endl;
    }
<<<<<<< HEAD

    float rate = getExchangeRate(date);
    float result = value * rate;
    if (result == -0)
        result = 0;
    
    std::cout << date << " => " << value << " = " << result << std::endl;
=======
    infile.close();
>>>>>>> 7abff59c0674373a6c82cb69d95588c48e0b5a70
}

std::string BitcoinExchange::trim(const std::string& s) const   {
    std::size_t start = 0;
    std::size_t end = s.size();
    while (start < s.size()
            && std::isspace(static_cast<unsigned char>(s[start])))
        ++start;
    while (end > start
            && std::isspace(static_cast<unsigned char>(s[end - 1])))
        --end;
    return (s.substr(start, end - start));
}

<<<<<<< HEAD
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
=======
bool    BitcoinExchange::isValidDate(const std::string& date) const {
    if (date.size() != 10 || date[4] != '-' || date[7] != '-')
        return false;
    
    for (std::size_t    i = 0; i < date.size(); ++i)    {
        if (i == 4 || i == 7)
            continue;
        if (!std::isdigit(static_cast<unsigned char>(date[i])))
>>>>>>> 7abff59c0674373a6c82cb69d95588c48e0b5a70
            return false;
    }

<<<<<<< HEAD
std::string BitcoinExchange::trim(const std::string& str) const {
    size_t start = str.find_first_not_of(" \t\r\n");
    if (start == std::string::npos)
        return "";
    
    size_t end = str.find_last_not_of(" \t\r\n");
    return str.substr(start, end - start + 1);
=======
    int year    = std::atoi(date.substr(0, 4).c_str());
    int month   = std::atoi(date.substr(5, 2).c_str());
    int day     = std::atoi(date.substr(8, 2).c_str());

    if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31)
        return false;

    return true;
>>>>>>> 7abff59c0674373a6c82cb69d95588c48e0b5a70
}