#include "AForm.hpp"
#include <iostream>

//Exception message implementations
const char* AForm::GradeTooHighException::what() const throw() {
    return "AForm::GradeTooHighException: grade is too high";
}

const char* AForm::GradeTooLowException::what() const throw() {
    return "AForm::GradeTooLowException: grade is too low";
}

const char* AForm::FormNotSignedException::what() const throw() {
    return "AForm::FormNotSignedException";
}

//Main constructor
AForm::AForm(const std::string& name, int signGrade, int execGrade)
    : name(name)
    , is_signed(false)
    , gradeToSign(signGrade)
    , gradeToExec(execGrade)
{
    if (signGrade < 1 || execGrade < 1)
        throw GradeTooHighException();
    if (signGrade > 150 || execGrade > 150)
        throw GradeTooLowException();
}

//Copy constructor
AForm::AForm(const AForm& other)
    : name(other.name)
    , is_signed(other.is_signed)
    , gradeToSign(other.gradeToSign)
    , gradeToExec(other.gradeToExec)
{}

//Assignment operator
// name, gradeToSign and gradeToExec are const and initialized only once
AForm& AForm::operator=(const AForm& other) {
    if (this != &other) {
        this->is_signed = other.is_signed;
    }
    return *this;
}

//Destructor
AForm::~AForm() {}

//Getters
const std::string& AForm::getName() const {
    return name;
}

bool AForm::isSigned() const {
    return is_signed;
}

int AForm::getSignGrade() const {
    return gradeToSign;
}

int AForm::getExecGrade() const {
    return gradeToExec;
}

//beSigned: called by a Bureaucrat to sign the AForm.
//Throws if the bureaucrat's grade is too low.
void AForm::beSigned(const Bureaucrat& b) {
    if (b.getGrade() > gradeToSign)
        throw GradeTooLowException();
    is_signed = true;
}

//Execute: Checks pre-conditions then calls the subclass's action()
void AForm::execute(const Bureaucrat& executor) const {
    if (!is_signed)
        throw FormNotSignedException();
    if (executor.getGrade() > gradeToExec)
        throw GradeTooLowException();
    action();
}

//Stream insertion overload
std::ostream& operator<<(std::ostream& os, const AForm& f) {
    os << "AForm \"" << f.getName() << "\": "
       << (f.isSigned() ? "signed" : "not signed")
       << ", sign grade "   << f.getSignGrade()
       << ", exec grade "   << f.getExecGrade();
    return os;
}