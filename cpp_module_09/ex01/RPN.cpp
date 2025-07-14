#include "RPN.hpp"
#include <sstream>
#include <cctype>

RPN::RPN()
{}

RPN::RPN(const RPN& other)  {
    (void)other;
}

RPN& RPN::operator=(const RPN& other)   {
    (void)other;
    return *this;
}

RPN::~RPN()
{}

int RPN::evaluate(const std::string& expression) const  {
    std::stack<int>     stack;
    std::istringstream  iss(expression);
    std::string         token;

    while (iss >> token) {
        if (token.size() == 1
            && std::isdigit(static_cast<unsigned char>(token[0])))  {
            stack.push(token[0] - '0');
        }
        else if ((token == "+") || token == "-" || token == "*"
            || (token == "/"))    {
            if (stack.size() < 2)
                throw std::runtime_error("Error");
            int b = stack.top();
            stack.pop();
            int a = stack.top();
            stack.pop();
            int r;
            switch (token[0])   {
                case    '+':
                    r = a + b;
                    break;
                case    '-':
                    r = a - b;
                    break;
                case    '*':
                    r = a * b;
                    break;
                case    '/':
                    if (b == 0)
                        throw   std::runtime_error("Error");
                    r = a / b;
                    break;
                default:
                    throw   std::runtime_error("Reached something that never should happen\n");
            }
            stack.push(r);
        }
        else    {
            throw   std::runtime_error("Error");
        }
    }
    if (stack.size() != 1)
        throw   std::runtime_error("Error");
    
    return stack.top();
}