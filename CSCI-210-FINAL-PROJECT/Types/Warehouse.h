#pragma once

#include <string>
#include "../property.h"

class Office;

class Warehouse
{
    friend class Product;
private:
    void* Database;
    size_t ID;

public:
    Warehouse ();

    enum class SizeType
    {
        BIG,
        MEDIUM,
        SMALL
    };

    property (Office, Warehouse, ::Office);
    property (SizeType, Warehouse, Warehouse::SizeType);
};
