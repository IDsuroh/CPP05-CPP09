#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <iostream>
#include <cstdlib> // for srand(), rand()
#include <ctime> // for time()

int main() {
    Bureaucrat boss("Boss", 1);
    Bureaucrat intern("Intern", 140);

    ShrubberyCreationForm shrub("home"); // 145, 137
    RobotomyRequestForm   robo("Bender"); // 75, 45
    PresidentialPardonForm pardon("Marvin"); // 25, 5

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
