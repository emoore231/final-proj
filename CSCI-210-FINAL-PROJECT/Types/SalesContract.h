#pragma once

#include <string>
#include <chrono>
#include "../property.h"

class Purchaser;
class Jurisdiction;
class Negotiater;
class Manager;

class SalesContract
{
    friend class Product;
private:
    void* Database;
    size_t ID;

public:
    SalesContract ();

    property (Purchaser, SalesContract, ::Purchaser);
    property (Jurisdiction, SalesContract, ::Jurisdiction);
    property (Negotiater, SalesContract, ::Negotiater);
    property (Manager, SalesContract, ::Manager);
    property (GrandTotal, SalesContract, size_t);
    property (Date, SalesContract, std::string);
};
