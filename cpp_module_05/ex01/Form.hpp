#ifndef FORM_HPP
#define FORM_HPP

#include <string>
#include <iostream>
#include <exception>
#include "Bureaucrat.hpp"

class Form {
private:
    const std::string name;
    bool              is_signed;
    const int         gradeToSign;
    const int         gradeToExec;
public:
    //–– Exceptions ––
    class GradeTooHighException : public std::exception {
    public:
        const char* what() const throw();
    };
    class GradeTooLowException : public std::exception {
    public:
        const char* what() const throw();
    };

    //–– Canonical form + main ctor ––
    Form(const std::string& name, int signGrade, int execGrade);
    Form(const Form& other);             // copy ctor
    Form& operator=(const Form& other);  // copy assign
    ~Form();                             // dtor

    //–– Getters ––
    const std::string& getName()      const;
    bool                isSigned()    const;
    int                 getSignGrade()const;
    int                 getExecGrade()const;

    //–– Action ––
    void beSigned(const Bureaucrat& b);
};

std::ostream& operator<<(std::ostream& os, const Form& f);

#endif