#pragma once

#include <string>
#include "../property.h"

class Negotiator;

class Manufacturer
{
private:
    void* Database;
    size_t ID;

public:
    Manufacturer ();

    property (Name, Manufacturer, std::string);
    property (ReliabilityIndex, Manufacturer, size_t);
    property (Negotiator, Manufacturer, ::Negotiator);
};
