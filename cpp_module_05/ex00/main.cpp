#include "Bureaucrat.hpp"

int main() {
    try {
        Bureaucrat a("Alice", 2);
        std::cout << a << std::endl; // Alice, bureaucrat grade 2
        a.increment();
        std::cout << a << std::endl; // Alice, bureaucrat grade 1
        a.increment();               // throws GradeTooHighException
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    try {
        Bureaucrat b("Bob", 151);    // throws GradeTooLowException
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}