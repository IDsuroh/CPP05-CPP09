#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include <iostream>

// Exception messages
const char* Bureaucrat::GradeTooHighException::what() const throw() {
    return "Grade cannot be higher than 1";
}
const char* Bureaucrat::GradeTooLowException::what() const throw() {
    return "Grade cannot be lower than 150";
}

// Main constructor
Bureaucrat::Bureaucrat(const std::string& name, int grade)
    : name(name)
{
    if (grade < 1)    throw GradeTooHighException();
    if (grade > 150)  throw GradeTooLowException();
    this->grade = grade;
}

// Copy-ctor
Bureaucrat::Bureaucrat(const Bureaucrat& other)
    : name(other.name), grade(other.grade) {}

// Assignment (only grade, name is const)
Bureaucrat& Bureaucrat::operator=(const Bureaucrat& other) {
    if (this != &other) {
        this->grade = other.grade;
    }
    return *this;
}

Bureaucrat::~Bureaucrat() {}

// Getters
const std::string& Bureaucrat::getName() const { return name; }
int                 Bureaucrat::getGrade() const { return grade; }

// Modifiers
void Bureaucrat::increment() {
    if (grade <= 1) throw GradeTooHighException();
    --grade;
}
void Bureaucrat::decrement() {
    if (grade >= 150) throw GradeTooLowException();
    ++grade;
}

void Bureaucrat::signForm(AForm& f) const {
  try {
    f.beSigned(*this);
    std::cout << name << " signed " << f.getName() << "\n";
  }
  catch (std::exception& e) {
    std::cout << name << " couldn’t sign "
              << f.getName()
              << " because " << e.what() << "\n";
  }
}

void Bureaucrat::executeForm(const AForm& f) const {
    try {
        f.execute(*this);
        std::cout << getName()
                  << " executed " << f.getName() << "\n";
    }
    catch (std::exception& e) {
        std::cout << getName()
                  << " couldn’t execute "
                  << f.getName()
                  << " because " << e.what() << "\n";
    }
}

// ostream overload
std::ostream& operator<<(std::ostream& os, const Bureaucrat& b) {
    os << b.getName() << ", bureaucrat grade " << b.getGrade();
    return os;
}