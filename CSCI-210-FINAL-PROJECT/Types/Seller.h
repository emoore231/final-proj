#pragma once

#include <string>
#include "../property.h"

class Jurisdiction;

class Seller
{
private:
    void* Database;
    size_t ID;

public:
    Seller ();

    property (Jurisdiction, Seller, ::Jurisdiction);
    property (Name, Seller, std::string);
    property (Reliabilirty, Seller, size_t);
};
