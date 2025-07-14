#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() 
{}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
    :   _database(other._database)
{}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)   {
    if (this != &other)
        _database = other._database;
    return *this;
}

BitcoinExchange::~BitcoinExchange()
{}

void    BitcoinExchange::loadDatabase(const std::string& filename)  {
    std::ifstream   file(filename.c_str());
    if (!file.is_open())
        throw std::runtime_error("Error:could not open database file.");

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
	if (std::getline(infile, line)) {
	if (line != "date | value") {
	    std::cerr << "Error: first line must be 'date | value'.\n";
	    infile.close();
	    return ;
	}
    } else {
	std::cout << "Empty input file.\n";
	infile.close();
	return ;
    }

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
            if (valueStr != "-0" && valueStr != "-0.0") {
                std::cerr << "Error: not a positive number.\n";
                continue;
            }
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
    infile.close();
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

bool    BitcoinExchange::isValidDate(const std::string& date) const {
    if (date.size() != 10 || date[4] != '-' || date[7] != '-')
        return false;
    
    for (std::size_t    i = 0; i < date.size(); ++i)    {
        if (i == 4 || i == 7)
            continue;
        if (!std::isdigit(static_cast<unsigned char>(date[i])))
            return false;
    }

    int year    = std::atoi(date.substr(0, 4).c_str());
    int month   = std::atoi(date.substr(5, 2).c_str());
    int day     = std::atoi(date.substr(8, 2).c_str());

    if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31)
        return false;

    return true;
}