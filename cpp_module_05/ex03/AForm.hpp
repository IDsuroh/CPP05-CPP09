#ifndef AForm_HPP
#define AForm_HPP

#include <string>
#include <iostream>
#include <exception>
#include "Bureaucrat.hpp"

class AForm {
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
    class FormNotSignedException : public std::exception {
        public:
        const char* what() const throw();
    };

    //–– Canonical AForm + main ctor ––
    AForm(const std::string& name, int signGrade, int execGrade);
    AForm(const AForm& other);             // copy ctor
    AForm& operator=(const AForm& other);  // copy assign
    virtual ~AForm();                     // virtual dtor

    //–– Getters ––
    const std::string&  getName()      const;
    bool                isSigned()    const;
    int                 getSignGrade()const;
    int                 getExecGrade()const;

    //–– Action ––
    void beSigned(const Bureaucrat& b);

    //–– Execution ––
    // 1) Checks isSigned and b.grade <= than exec Grade, else Throw.
    // 2) Calls the subclass's action()
    void execute(const Bureaucrat& executor) const;

    virtual void action() const = 0;
};

std::ostream& operator<<(std::ostream& os, const AForm& f);

#endif