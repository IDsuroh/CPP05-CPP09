#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <iostream>

int main() {
    Bureaucrat boss("Boss", 1);
    Bureaucrat intern("Intern", 140);

    ShrubberyCreationForm shrub("home");
    RobotomyRequestForm   robo("Bender");
    PresidentialPardonForm pardon("Marvin");

    // signing
    intern.signForm(shrub);   // OK (140 ≤ 145)
    boss.signForm(robo);      // OK (1 ≤ 72)
    boss.signForm(pardon);    // OK

    std::cout << "\n";

    // executing
    intern.executeForm(shrub);    // OK (140 ≤ 137? no → exception)
    boss.executeForm(shrub);      // OK
    boss.executeForm(robo);       // drilling + success/fail
    boss.executeForm(pardon);     // pardon message

    return 0;
}
