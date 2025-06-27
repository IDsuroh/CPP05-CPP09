#include "RPN.hpp"

RPN::RPN() {}

RPN::RPN(const RPN& other) : _stack(other._stack) {}

RPN& RPN::operator=(const RPN& other) {
    if (this != &other) {
        _stack = other._stack;
    }
    return *this;
}

RPN::~RPN() {}

double RPN::calculate(const std::string& expression) {
    std::istringstream iss(expression);
    std::string token;
    
    // Clear the stack for fresh calculation
    while (!_stack.empty()) {
        _stack.pop();
    }
    
    while (iss >> token) {
        token = trim(token);
        
        if (token.empty()) {
            continue;
        }
        
        if (isNumber(token)) {
            double num = std::atof(token.c_str());
            _stack.push(num);
        }
        else if (isOperator(token)) {
            if (_stack.size() < 2) {
                throw std::runtime_error("Error");
            }
            
            // Pop two operands (note the order!)
            double b = _stack.top(); _stack.pop();
            double a = _stack.top(); _stack.pop();
            
            double result = performOperation(a, b, token);
            _stack.push(result);
        }
        else {
            throw std::runtime_error("Error");
        }
    }
    
    if (_stack.size() != 1) {
        throw std::runtime_error("Error");
    }
    
    return _stack.top();
}

bool RPN::isOperator(const std::string& token) const {
    return token == "+" || token == "-" || token == "*" || token == "/";
}

bool RPN::isNumber(const std::string& token) const {
    if (token.empty()) {
        return false;
    }
    
    size_t start = 0;
    // Handle negative numbers
    if (token[0] == '-' || token[0] == '+') {
        if (token.length() == 1) {
            return false; // Just a sign is not a number
        }
        start = 1;
    }
    
    // Check if all remaining characters are digits
    for (size_t i = start; i < token.length(); ++i) {
        if (!std::isdigit(token[i])) {
            return false;
        }
    }
    
    // Additional check: numbers should be less than 10 (single digit)
    // But negative numbers and results can be larger
    double num = std::atof(token.c_str());
    if (num >= 0 && num >= 10) {
        return false;
    }
    if (num < 0 && num <= -10) {
        return false;
    }
    
    return true;
}

double RPN::performOperation(double a, double b, const std::string& op) const {
    if (op == "+") {
        return a + b;
    }
    else if (op == "-") {
        return a - b;
    }
    else if (op == "*") {
        return a * b;
    }
    else if (op == "/") {
        if (b == 0) {
            throw std::runtime_error("Error");
        }
        return a / b;
    }
    else {
        throw std::runtime_error("Error");
    }
}

std::string RPN::trim(const std::string& str) const {
    size_t start = str.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) {
        return "";
    }
    
    size_t end = str.find_last_not_of(" \t\r\n");
    return str.substr(start, end - start + 1);
}