#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include <stdint.h>  // For uintptr_t
#include "Data.hpp"

class Serializer {
private:
    // Orthodox Canonical Form - made private to prevent instantiation
    Serializer();
    Serializer(const Serializer& other);
    Serializer& operator=(const Serializer& other);
    ~Serializer();

public:
    static uintptr_t serialize(Data* ptr);
    static Data* deserialize(uintptr_t raw);
};

#endif