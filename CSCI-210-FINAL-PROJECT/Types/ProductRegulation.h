#pragma once

#include <string>
#include "../property.h"

class ProductCategory;
class Regulation;

class ProductRegulation
{
private:
    void* Database;
    size_t ID;

public:
    ProductRegulation ();

    property (ProductCategory, ProductRegulation, ::ProductCategory);
    property (Regulation, ProductRegulation, ::Regulation);
};
