#pragma once

#include <string>
#include "../property.h"

class Manufacturer;
class ProductCategory;

class ProductType
{
    friend class Product;
private:
    void* Database;
    size_t ID;

public:
    ProductType ();

    property (Manufacturer, ProductType, ::Manufacturer);
    property (ProductCategory, ProductType, ::ProductCategory);
    property (Name, ProductType, std::string);
    property (Description, ProductType, std::string);
    property (DemandIndex, ProductType, std::string);
};
