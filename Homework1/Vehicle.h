#pragma once
#include <cstddef>

#include "MyString.h"

class Vehicle {
    MyString registrationNumber;
    MyString desc;
    std::size_t vehSpace;

public:
    Vehicle(const char* registration, const char* description, std::size_t space);

    const char* registration() const;
    const char* description() const;
    std::size_t space() const;
};