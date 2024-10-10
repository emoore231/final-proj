#pragma once

#include <string>
#include <chrono>
#include "../property.h"

class Seller;
class Jurisdiction;
class Negotiater;
class Manager;

class AcquisitionContract
{
    friend class Product;
private:
    void* Database;
    size_t ID;

public:
    AcquisitionContract (const size_t ID, void* Database);

    property (Seller, AcquisitionContract, ::Seller);
    property (Jurisdiction, AcquisitionContract, ::Jurisdiction);
    property (Negotiater, AcquisitionContract, ::Negotiater);
    property (Manager, AcquisitionContract, ::Manager);
    property (GrandTotal, AcquisitionContract, size_t);
    property (Date, AcquisitionContract, std::string);
};
