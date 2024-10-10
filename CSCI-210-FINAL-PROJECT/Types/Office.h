#pragma once

#include <string>
#include "../property.h"

class Location;
class Jurisdiction;

class Office
{
private:
    void* Database;
    size_t ID;

public:
    Office ();

    property (Jurisdiction, Office, ::Jurisdiction);
    property (Location, Office, ::Location);
};
