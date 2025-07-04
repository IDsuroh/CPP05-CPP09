#include "ScalarConverter.hpp"

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <value>" << std::endl;
        return 1;
    }
    
    int argc_as_char = static_cast<int>(std::atoi(argv[1]));
    std::cout << "Example: " << argc_as_char << " << I changed the type of argc to char just for example" << std::endl;

    ScalarConverter::convert(argv[1]);
    
    return 0;
}