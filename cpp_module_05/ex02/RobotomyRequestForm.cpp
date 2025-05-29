#include "RobotomyRequestForm.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

RobotomyRequestForm::RobotomyRequestForm(const std::string& tgt)
  : AForm("Robotomy", 72, 45),
    target(tgt)
{
    std::srand(std::time(NULL));
}

RobotomyRequestForm::~RobotomyRequestForm() {}

void RobotomyRequestForm::action() const {
    std::cout << "* drilling noises *\n";
    if (std::rand() % 2)
        std::cout << target << " has been robotomized successfully.\n";
    else
        std::cout << "Robotomy failed on " << target << ".\n";
}