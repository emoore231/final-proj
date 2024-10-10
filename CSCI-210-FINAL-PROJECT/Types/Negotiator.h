#pragma once

#include <string>
#include "../property.h"

class Employee;

class Negotiator
{
private:
    void* Database;
    size_t ID;

public:
    Negotiator ();

    property (Employee, Negotiator, ::Employee);
    property (Favoribility, Negotiator, size_t);
};