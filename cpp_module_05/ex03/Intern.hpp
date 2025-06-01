#ifndef INTERN_HPP
#define INTERN_HPP

#include <string>
#include <iostream>
#include "AForm.hpp"

class ShrubberyCreationForm;
class RobotomyRequestForm;
class PresidentialPardonForm;

class Intern {
public:
    Intern();
    Intern(const Intern& other);
    Intern& operator=(const Intern&);
    ~Intern();

    AForm* makeForm(const std::string& formName,
                    const std::string& target) const;
};

#endif