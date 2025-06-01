#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "Intern.hpp"

#include <iostream>

int main() {
    Intern  someIntern;
    AForm*  formPtr;

    std::cout << "\n-- TEST #1: Create a valid ‘robotomy request’ --\n";
    formPtr = someIntern.makeForm("robotomy request", "Bender");
    if (formPtr) {
        std::cout << *formPtr << "\n";
        delete formPtr;
    }

    std::cout << "\n-- TEST #2: Create an invalid form --\n";
    formPtr = someIntern.makeForm("unknown form", "TargetX");
    if (formPtr) {
        delete formPtr;  // shouldn’t happen
    }

    std::cout << "\n-- TEST #3: Create a shrubbery form and execute it --\n";
    formPtr = someIntern.makeForm("shrubbery creation", "home");
    if (formPtr) {
        Bureaucrat boss("Boss", 1);
        std::cout << *formPtr << "\n";
        boss.signForm(*formPtr);
        boss.executeForm(*formPtr);
        delete formPtr;  
    }

    std::cout << "\n-- TEST #4: Create a presidential pardon form --\n";
    formPtr = someIntern.makeForm("presidential pardon", "Marvin");
    if (formPtr) {
        Bureaucrat boss("Boss", 1);
        std::cout << *formPtr << "\n";
        boss.signForm(*formPtr);
        boss.executeForm(*formPtr);
        delete formPtr;
    }

    return 0;
}