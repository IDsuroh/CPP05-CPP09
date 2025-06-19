#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter() {}

ScalarConverter::ScalarConverter(const ScalarConverter& other)  {
    (void)other;
}

ScalarConverter& ScalarConverter::operator=(const ScalarConverter& other)   {
    (void)other;
    return *this;
}

ScalarConverter::~ScalarConverter() {}

InputType ScalarConverter::detectType(const std::string& str) {
    
    if (str == "nan" || str == "nanf")
        return TYPE_NAN;

    if (str == "+inf" || str == "+inff")
        return TYPE_PLUS_INF;

    if (str == "-inf" || str == "-inff")
        return TYPE_MINUS_INF;

    if ((str.length() == 3 && str[0] == '\"' && str[2] == '\"')
        || (str.length() == 3 && str[0] == '\'' && str[2] == '\'')
        || (str.length() == 1 && !std::isdigit(str[0])))
        return TYPE_CHAR;

    if (!str.empty() && str[str.length() - 1] == 'f'
        && str.find('.') != std::string::npos) 
        return TYPE_FLOAT;

    if (str.find('.') != std::string::npos)
        return TYPE_DOUBLE;
    
    char* endptr;
    strtol(str.c_str(), &endptr, 10);
    return (*endptr == '\0') ? TYPE_INT : TYPE_INVALID;
}

void ScalarConverter::convert(const std::string& str) {
    
    InputType type = detectType(str);
    double value = 0;
    bool impossible = false;
    
    switch (type) {
        
        case TYPE_CHAR:
            if ((str.length() == 3 && str[0] == '\'' && str[2] == '\'')
                || (str.length() == 3 && str[0] == '\"' && str[2] == '\"'))
                value = static_cast<double>(str[1]);
            else if (str.length() == 1)
                value = static_cast<double>(str[0]);
            break;
        
        case TYPE_INT:
            value = static_cast<double>(atoi(str.c_str()));
            break;
        
        case TYPE_FLOAT:
            value = static_cast<double>(atof(str.c_str()));
            break;
        
        case TYPE_DOUBLE:
            value = atof(str.c_str());
            break;
        
        case TYPE_NAN:
            value = std::numeric_limits<double>::quiet_NaN();
            break;
        //What is quiet_NaN()?
        //  quiet_NaN() is a static function that returns
        //  a special floating-point value representing "Not a Number".
    
        case TYPE_PLUS_INF:
            value = std::numeric_limits<double>::infinity();
            break;
    
        case TYPE_MINUS_INF:
            value = -std::numeric_limits<double>::infinity();
            break;
        
        case TYPE_INVALID:
            default:
            impossible = true;
            break;
    }
    
    // Print results (same printing logic as before)
    
    // char:
    std::cout << "char: ";
    if (impossible || std::isnan(value) || std::isinf(value) 
        || value < 0 || value > 127) {
        std::cout << "impossible";
    } else if (value < 32 || value > 126) {
        std::cout << "Non displayable";
    } else {
        std::cout << "'" << static_cast<char>(value) << "'";
    }
    std::cout << std::endl;
    
    // int:
    std::cout << "int: ";
    if (impossible || std::isnan(value) || std::isinf(value)
        || value < std::numeric_limits<int>::min()
        || value > std::numeric_limits<int>::max()) {
        std::cout << "impossible";
    } else {
        std::cout << static_cast<int>(value);
    }
    std::cout << std::endl;
    
    // float:
    std::cout << "float: ";
    if (impossible) {
        std::cout << "impossible";
    } else if (std::isnan(value)) {
        std::cout << "nanf";
    } else if (std::isinf(value)) {
        std::cout << (value > 0 ? "+inff" : "-inff");
    } else {
        std::cout << std::fixed << std::setprecision(1)
            << static_cast<float>(value) << "f";
    }
    std::cout << std::endl;
    
    // double:
    std::cout << "double: ";
    if (impossible) {
        std::cout << "impossible";
    } else if (std::isnan(value)) {
        std::cout << "nan";
    } else if (std::isinf(value)) {
        std::cout << (value > 0 ? "+inf" : "-inf");
    } else {
        std::cout << std::fixed << std::setprecision(1) << value;
    }
    std::cout << std::endl;
}