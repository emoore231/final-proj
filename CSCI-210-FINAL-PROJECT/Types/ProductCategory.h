#pragma once

#include <string>
#include "../property.h"

class ProductCategory
{
private:
    void* Database;
    size_t ID;

public:
    ProductCategory ();

    property (Name, ProductCategory, std::string);
    property (Description, ProductCategory, std::string);
};
