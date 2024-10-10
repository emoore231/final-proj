#pragma once

#include <string>
#include "../property.h"

class Jurisdiction;

class Regulation
{
private:
    void* Database;
    size_t ID;

public:
    Regulation ();

    property (Jurisdiction, Regulation, ::Jurisdiction);
    property (LegalCode, Regulation, std::string);
    property (AuthoringBody, Regulation, std::string);
};
