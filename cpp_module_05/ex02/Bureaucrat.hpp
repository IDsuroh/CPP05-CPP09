#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <string>
#include <iostream>
#include <exception>

class AForm;

class Bureaucrat {
private:
    const std::string name;
    int               grade;
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
    Bureaucrat(const std::string& name, int grade);
    Bureaucrat(const Bureaucrat& other);
    ~Bureaucrat();
    Bureaucrat& operator=(const Bureaucrat& other);

    //–– Getters ––
    const std::string& getName() const;
    int                 getGrade() const;

    void signForm(AForm& f) const;

    //–– Grade modifiers ––
    void increment();   // raises rank (grade--)
    void decrement();   // lowers rank (grade++)

    void executeForm(const AForm& form) const;
};

//–– ostream overload ––
std::ostream& operator<<(std::ostream& os, const Bureaucrat& b);

#endif