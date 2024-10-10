#pragma once

#include <string>
#include "../property.h"

class JobPosition
{
private:
    void* Database;
    size_t ID;

public:
    JobPosition (const size_t _ID, void* _Database);

    property (Name, JobPosition, std::string);
    property (Description, JobPosition, std::string);
};
