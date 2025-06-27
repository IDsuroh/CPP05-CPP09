#ifndef RPN_HPP
#define RPN_HPP

#include <stack>
#include <string>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <cstdlib>

class RPN {
private:
    std::stack<double> _stack;
    
    bool isOperator(const std::string& token) const;
    bool isNumber(const std::string& token) const;
    double performOperation(double a, double b, const std::string& op) const;
    std::string trim(const std::string& str) const;
    
public:
    RPN();
    RPN(const RPN& other);
    RPN& operator=(const RPN& other);
    ~RPN();
    
    double calculate(const std::string& expression);
};

#endif