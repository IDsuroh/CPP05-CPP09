#include "Form.hpp"
#include <iostream>

//Exception message implementations
const char* Form::GradeTooHighException::what() const throw() {
    return "from Form::GradeTooHighException: grade is too high (must be ≥ 1)";
}

const char* Form::GradeTooLowException::what() const throw() {
    return "from Form::GradeTooLowException: grade is too low (must be ≤ 150)";
}

//Main constructor
Form::Form(const std::string& name, int signGrade, int execGrade)
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
Form::Form(const Form& other)
    : name(other.name)
    , is_signed(other.is_signed)
    , gradeToSign(other.gradeToSign)
    , gradeToExec(other.gradeToExec)
{}

//Assignment operator
// name, gradeToSign and gradeToExec are const and initialized only once
Form& Form::operator=(const Form& other) {
    if (this != &other) {
        this->is_signed = other.is_signed;
    }
    return *this;
}

//Destructor
Form::~Form() {}

//Getters
const std::string& Form::getName() const {
    return name;
}

bool Form::isSigned() const {
    return is_signed;
}

int Form::getSignGrade() const {
    return gradeToSign;
}

int Form::getExecGrade() const {
    return gradeToExec;
}

//beSigned: called by a Bureaucrat to sign the form.
//Throws if the bureaucrat's grade is too low.
void Form::beSigned(const Bureaucrat& b) {
    if (b.getGrade() > gradeToSign)
        throw GradeTooLowException();
    is_signed = true;
}

//Stream insertion overload
std::ostream& operator<<(std::ostream& os, const Form& f) {
    os << "Form \"" << f.getName() << "\": "
       << (f.isSigned() ? "signed" : "not signed")
       << ", sign grade "   << f.getSignGrade()
       << ", exec grade "   << f.getExecGrade();
    return os;
}