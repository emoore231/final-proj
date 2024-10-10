#pragma once

#include <string>
#include "../property.h"

class Warehouse;
class Manager;

class Transfer
{
    friend class Product;
private:
    void* Database;
    size_t ID;

public:
    Transfer ();

    property (Origin, Transfer, ::Warehouse);
    property (Destination, Transfer, ::Warehouse);
    property (Manager, Transfer, ::Manager);
};
