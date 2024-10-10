#pragma once

#include <string>
#include "../property.h"

class ProductType;
class Warehouse;

class ProductCapacity
{
private:
    void* Database;
    size_t ID;

public:
    ProductCapacity ();

    property (ProductType, ProductCapacity, ::ProductType);
    property (Warehouse, ProductCapacity, ::Warehouse);
    property (MaxCapacity, ProductCapacity, size_t);
    property (Restrictions, ProductCapacity, std::string);
};
