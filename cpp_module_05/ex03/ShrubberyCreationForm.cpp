#include "ShrubberyCreationForm.hpp"
#include <fstream>   // for std::ofstream

ShrubberyCreationForm::ShrubberyCreationForm(const std::string& target)
  : AForm("ShrubberyCreationForm", 145, 137)
  , target(target)
{}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& other)
  : AForm(other)
  , target(other.target)
{}

ShrubberyCreationForm& ShrubberyCreationForm::operator=(const ShrubberyCreationForm& other)
{
    if (this != &other) {
        AForm::operator=(other);
    }
    return *this;
}

ShrubberyCreationForm::~ShrubberyCreationForm()
{}

void ShrubberyCreationForm::action() const {
    // build the filename
    std::string filename = target + "_shrubbery";
    std::ofstream ofs(filename.c_str());
    if (!ofs) {
        std::cerr << "Error: could not open " << filename << "\n";
        return;
    }

    ofs << "    _-_\n"
           "  /~~   ~~\\\n"
           " /~~       ~~\\\n"
           " {   树   }\n"
           "  \\  树  /\n"
           "   \\_~~_/\n";
}