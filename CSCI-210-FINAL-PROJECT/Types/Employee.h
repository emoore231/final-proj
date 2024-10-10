#pragma once

#include <string>
#include "../property.h"

class Office;
class Schedule;
class JobPosition;
class Location;
class Jurisdiction;
class Manager;

class Employee
{
private:
    void* Database;
    size_t ID;

public:
    Employee (const size_t _ID, void* _Database);

    property (Name, Employee, std::string);
    property (SSN, Employee, size_t);
    property (DOB, Employee, size_t);
    property (Office, Employee, ::Office);
    property (Salary, Employee, size_t);
    property (Schedule, Employee, ::Schedule);
    property (JobPosition, Employee, ::JobPosition);
    property (Location, Employee, ::Location);
    property (Jurisdiction, Employee, ::Jurisdiction);
    property (Manager, Employee, ::Manager);
};
