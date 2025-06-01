#include "PresidentialPardonForm.hpp"
#include <iostream>

PresidentialPardonForm::PresidentialPardonForm(const std::string& target)
  : AForm("PresidentialPardon", 25, 5)
  , target(target)
{}

PresidentialPardonForm::~PresidentialPardonForm() {}

void PresidentialPardonForm::action() const {
    std::cout << target
              << " has been pardoned by Zaphod Beeblebrox.\n";
}