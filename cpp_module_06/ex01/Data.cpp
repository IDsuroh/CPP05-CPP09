#include "Data.hpp"

Data::Data(int i, const std::string& n, double v, char g) 
    : id(i), name(n), value(v), grade(g) {}

Data::Data()
    : id(0), name(""), value(0.0), grade('F') {}