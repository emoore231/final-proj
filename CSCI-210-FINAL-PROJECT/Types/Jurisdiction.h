#pragma once

#include <string>
#include "../property.h"

class Jurisdiction
{
private:
    void* Database;
    size_t ID;

public:
    Jurisdiction (const size_t _ID, void* _Database);

    property (State, Jurisdiction, std::string);
    property (County, Jurisdiction, std::string);
    property (City, Jurisdiction, std::string);
};
