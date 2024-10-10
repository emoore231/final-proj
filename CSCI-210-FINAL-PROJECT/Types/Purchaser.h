#pragma once

#include <string>
#include "../property.h"

class Jurisdiction;

class Purchaser
{
private:
    void* Database;
    size_t ID;

public:
    enum class Kind
    {
        GENERAL_PUBLIC,
        AUTHORIZED_CONTRACTOR
    };

    Purchaser ();

    property (Kind, Purchaser, Purchaser::Kind);
    property (Name, Purchaser, std::string);
    property (Jurisdiction, Purchaser, ::Jurisdiction);
    property (Telephone, Purchaser, size_t);
    property (NRANumber, Purchaser, std::string);
    property (DLNNumber, Purchaser, std::string);
    property (ATFNumber, Purchaser, std::string);
};
