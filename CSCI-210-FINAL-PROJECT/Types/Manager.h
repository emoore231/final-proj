#pragma once

#include <string>
#include "../property.h"

class Employee;

class Manager
{
private:
    void* Database;
    size_t ID;

public:
    Manager ();

    property (Employee, Manager, ::Employee);
    property (AuthorityLevel, Manager, size_t);
    property (Notes, Manager, std::string);
};
