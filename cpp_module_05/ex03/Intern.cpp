#include "Intern.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

static AForm* createShrub(const std::string& target)    {
    return new ShrubberyCreationForm(target);
}

static AForm* createRobotomy(const std::string& target) {
    return new RobotomyRequestForm(target);
}

static AForm* createPardon(const std::string& target)   {
    return new PresidentialPardonForm(target);
}

Intern::Intern()
{}

Intern::Intern(const Intern& other) {
    (void)other;
}

Intern& Intern::operator=(const Intern& other)  {
    (void)other;
    return *this;
}

Intern::~Intern()
{}

AForm* Intern::makeForm(const std::string& formName,
                        const std::string& target) const    {
    struct FormPair {
        const char* name;
        AForm*  (*create)(const std::string& target);
    };
    static FormPair const formTable[] = {
        {"shrubbery creation", createShrub},
        {"robotomy request", createRobotomy},
        {"presidential pardon", createPardon}
    };
    const size_t n = sizeof(formTable) / sizeof(FormPair);
    for (size_t i = 0; i < n; ++i) {
        if (formName == formTable[i].name)  {
            std::cout << "Intern creates " << formName << "\n";
            return formTable[i].create(target);
        }
    }
    std::cout
            << "Intern could not create \"" << formName
            << "\" because form name not recognized\n";
    return NULL;
}