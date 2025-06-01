#include "RobotomyRequestForm.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

RobotomyRequestForm::RobotomyRequestForm(const std::string& tgt)
  : AForm("Robotomy", 72, 45),
    target(tgt)
{
    static unsigned counter = 0;
    unsigned seed = static_cast<unsigned>(std::time(NULL)) ^ (++counter);
    std::srand(seed);
}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& other)
  : AForm(other)
  , target(other.target)
{}

RobotomyRequestForm& RobotomyRequestForm::operator=(const RobotomyRequestForm& other)
{
    if (this != &other) {
        AForm::operator=(other);
    }
    return *this;
}

RobotomyRequestForm::~RobotomyRequestForm()
{}

void RobotomyRequestForm::action() const {
    std::cout << "* drilling noises *\n";
    if (std::rand() % 2)
        std::cout << target << " has been robotomized successfully.\n";
    else
        std::cout << "Robotomy failed on " << target << ".\n";
}