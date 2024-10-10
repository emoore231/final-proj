#pragma once

#include <string>

struct Queries final
{
	virtual ~Queries () = 0;

    static const std::string CREATE_PRODUCT;
    static const std::string INDEX_PRODUCT;
    static const std::string FOREIGN_KEY_PRODUCT;

    static const std::string CREATE_PRODUCT_TYPE;
    static const std::string INDEX_PRODUCT_TYPE;
    static const std::string FOREIGN_KEY_PRODUCT_TYPE;

    static const std::string CREATE_PRODUCT_CATEGORY;
    static const std::string INDEX_PRODUCT_CATEGORY;
    static const std::string FOREIGN_KEY_PRODUCT_CATEGORY;

    static const std::string CREATE_REGULATION;
    static const std::string INDEX_REGULATION;
    static const std::string FOREIGN_KEY_REGULATION;

    static const std::string CREATE_SALES_CONTRACT;
    static const std::string INDEX_SALES_CONTRACT;
    static const std::string FOREIGN_KEY_SALES_CONTRACT;

    static const std::string CREATE_ACQUISITION_CONTRACT;
    static const std::string INDEX_ACQUISITION_CONTRACT;
    static const std::string FOREIGN_KEY_ACQUISITION_CONTRACT;

    static const std::string CREATE_TRANSFER;
    static const std::string INDEX_TRANSFER;
    static const std::string FOREIGN_KEY_TRANSFER;

    static const std::string CREATE_PRODUCT_CAPACITY;
    static const std::string INDEX_PRODUCT_CAPACITY;
    static const std::string FOREIGN_KEY_PRODUCT_CAPACITY;

    static const std::string CREATE_PRODUCT_REGULATION;
    static const std::string INDEX_PRODUCT_REGULATION;
    static const std::string FOREIGN_KEY_PRODUCT_REGULATION;

    static const std::string CREATE_PURCHASER;
    static const std::string INDEX_PURCHASER;
    static const std::string FOREIGN_KEY_PURCHASER;

    static const std::string CREATE_SELLER;
    static const std::string INDEX_SELLER;
    static const std::string FOREIGN_KEY_SELLER;

    static const std::string CREATE_WAREHOUSE;
    static const std::string INDEX_WAREHOUSE;
    static const std::string FOREIGN_KEY_WAREHOUSE;

    static const std::string CREATE_MANUFACTURER;
    static const std::string INDEX_MANUFACTURER;
    static const std::string FOREIGN_KEY_MANUFACTURER;

    static const std::string CREATE_LOCATION;
    static const std::string INDEX_LOCATION;
    static const std::string FOREIGN_KEY_LOCATION;

    static const std::string CREATE_OFFICE;
    static const std::string INDEX_OFFICE;
    static const std::string FOREIGN_KEY_OFFICE;

    static const std::string CREATE_JURISDICTION;
    static const std::string INDEX_JURISDICTION;
    static const std::string FOREIGN_KEY_JURISDICTION;

    static const std::string CREATE_NEGOTIATOR;
    static const std::string INDEX_NEGOTIATOR;
    static const std::string FOREIGN_KEY_NEGOTIATOR;

    static const std::string CREATE_MANAGER;
    static const std::string INDEX_MANAGER;
    static const std::string FOREIGN_KEY_MANAGER;

    static const std::string CREATE_EMPLOYEE;
    static const std::string INDEX_EMPLOYEE;
    static const std::string FOREIGN_KEY_EMPLOYEE;

    static const std::string CREATE_SCHEDULE;
    static const std::string INDEX_SCHEDULE;
    static const std::string FOREIGN_KEY_SCHEDULE;

    static const std::string CREATE_EMPLOYEE_CHANGE;
    static const std::string INDEX_EMPLOYEE_CHANGE;
    static const std::string FOREIGN_KEY_EMPLOYEE_CHANGE;

    static const std::string CREATE_JOB_POSITION;
    static const std::string INDEX_JOB_POSITION;
    static const std::string FOREIGN_KEY_JOB_POSITION;




};

