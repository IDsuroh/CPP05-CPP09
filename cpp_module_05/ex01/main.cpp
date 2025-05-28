// main.cpp
#include "Bureaucrat.hpp"
#include "Form.hpp"
#include <iostream>

int main() {
    std::cout << "=== Form Creation Tests ===\n";
    // Invalid sign-/exec‐grade combinations
    try {
        Form f1("TooHighSign", 0, 10);
    }
    catch (std::exception& e) {
        std::cerr << "Expected exception for signGrade=0: " << e.what() << "\n";
    }
    try {
        Form f2("TooLowSign", 151, 10);
    }
    catch (std::exception& e) {
        std::cerr << "Expected exception for signGrade=151: " << e.what() << "\n";
    }
    try {
        Form f3("TooHighExec", 10, 0);
    }
    catch (std::exception& e) {
        std::cerr << "Expected exception for execGrade=0: " << e.what() << "\n";
    }
    try {
        Form f4("TooLowExec", 10, 151);
    }
    catch (std::exception& e) {
        std::cerr << "Expected exception for execGrade=151: " << e.what() << "\n\n";
    }

    std::cout << "=== Successful Form & Bureaucrat Creation ===\n";
    Bureaucrat alice("Alice", 45);
    Bureaucrat bob("Bob", 75);
    Form taxForm("TaxForm", 50, 25);
    std::cout << alice << "\n" << bob << "\n" << taxForm << "\n\n";

    std::cout << "=== Signing Attempts ===\n";
    // Bob (grade 75) tries first: should fail (75 > 50)
    bob.signForm(taxForm);
    std::cout << taxForm << "\n\n";

    // Alice (grade 45) signs successfully
    alice.signForm(taxForm);
    std::cout << taxForm << "\n\n";

    std::cout << "=== Double-Signing ===\n";
    // Signing an already-signed form (no exception in ex01 spec)
    alice.signForm(taxForm);
    std::cout << taxForm << "\n\n";

    std::cout << "=== Copy & Assignment of Form ===\n";
    // Copy constructor
    Form copyConstructed(taxForm);
    std::cout << "Copy-constructed: " << copyConstructed << "\n";
    // Assignment operator
    Form assignedForm("Placeholder", 100, 100);
    std::cout << "Before assignment: " << assignedForm << "\n";
    assignedForm = taxForm;
    std::cout << "After assignment:  " << assignedForm << "\n";

    return 0;
}