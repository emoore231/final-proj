#pragma once

#include <string>
#include "../property.h"


class Location
{
private:
    void* Database;
    size_t ID;

public:
    Location ();

    property (AddressLine1, Location, std::string);
    property (AddressLine2, Location, std::string);
    property (State, Location, std::string);
    property (City, Location, std::string);
    property (ZipCode, Location, size_t);
};
