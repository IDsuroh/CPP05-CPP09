#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <string>
#include <iostream>
#include <limits>
#include <cmath>
#include <iomanip>
#include <cstdlib>

enum InputType {
    TYPE_CHAR,
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_DOUBLE,
    TYPE_NAN,
    TYPE_PLUS_INF,
    TYPE_MINUS_INF,
    TYPE_INVALID
};

class ScalarConverter {
private:
    ScalarConverter();
    ScalarConverter(const ScalarConverter& other);
    ScalarConverter& operator=(const ScalarConverter& other);
    ~ScalarConverter();

    static InputType detectType(const std::string& str);

public:
    static void convert(const std::string& str);
};

#endif