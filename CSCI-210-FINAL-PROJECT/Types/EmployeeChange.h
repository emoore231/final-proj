#pragma once

#include <string>
#include "../property.h"

class Employee;
class Manager;

class EmployeeChange
{
private:
    void* Database;
    size_t ID;

public:
    enum class Kind
    {
        HIRE,
        FIRE,
        RESIGN_DISGRACE,
        RESIGN,
        RETIRE_DISGRACE,
        RETIRE,
        SUSPEND_BEGIN,
        SUSPEND_END,
    };

    EmployeeChange (const size_t _ID, void* _Database);

    property (Employee, EmployeeChange, ::Employee);
    property (Manager, EmployeeChange, ::Manager);
    property (Date, EmployeeChange, std::string);
    property (Kind, EmployeeChange, EmployeeChange::Kind);

};
