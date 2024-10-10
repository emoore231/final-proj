#pragma once

#include <string>
#include <map>
#include <vector>

namespace SQL
{
	class Transaction;
}

#include <setjmp.h>

//my old friend
extern jmp_buf jpr;

//the access level of the user
extern int accessLevel;
//if the database is in a transaction
extern bool inTransaction;
//this is only allocated if there is a transaction
extern SQL::Transaction* currentTransactionDatabase;
extern int currentTransactionOperationCount;

inline void HandleIstreamFailure ()
{
    if (std::cin.eof ())
        std::cout << "EOF DETECTED ON STDIN, TERMINATING\nTHANKS BASH!", exit (1);

    std::cout << "OPTION NOT RECOGNIZED" << std::endl;
    std::cin.clear ();
    std::string s;
    std::cin >> s;
}

typedef bool (*fptr_t)();

#define lf std::endl


//list of tables
enum class Table
{
	JURISDICTION,
	LOCATION,
	MANUFACTURER,
	SCHEDULE,
	JOB_POSITION,
	PRODUCT_CATEGORY,
	PRODUCT_TYPE,
	REGULATION,
	PURCHASER,
	SELLER,
	OFFICE,
	EMPLOYEE,
	PRODUCT_REGULATION,
	WAREHOUSE,
	MANAGER,
	MANAGEMENT,
	NEGOTIATER,
	SALES_CONTRACT,
	ACQUISITION_CONTRACT,
	PRODUCT,
	TRANSFER,
	PRODUCT_CAPACITY,
	PRODUCT_CAPACITY_RESTRICTION,
	EMPLOYEE_CHANGE,
};

//list of types / fk constraints
enum class Type
{
	JURISDICTION = Table::JURISDICTION,
	LOCATION = Table::LOCATION,
	MANUFACTURER = Table::MANUFACTURER,
	SCHEDULE = Table::SCHEDULE,
	JOB_POSITION = Table::JOB_POSITION,
	PRODUCT_CATEGORY = Table::PRODUCT_CATEGORY,
	PRODUCT_TYPE = Table::PRODUCT_TYPE,
	REGULATION = Table::REGULATION,
	PURCHASER = Table::PURCHASER,
	SELLER = Table::SELLER,
	OFFICE = Table::OFFICE,
	EMPLOYEE = Table::EMPLOYEE,
	PRODUCT_REGULATION = Table::PRODUCT_REGULATION,
	WAREHOUSE = Table::WAREHOUSE,
	MANAGER = Table::MANAGER,
	MANAGEMENT = Table::MANAGEMENT,
	NEGOTIATER = Table::NEGOTIATER,
	SALES_CONTRACT = Table::SALES_CONTRACT,
	ACQUISITION_CONTRACT = Table::ACQUISITION_CONTRACT,
	PRODUCT = Table::PRODUCT,
	TRANSFER = Table::TRANSFER,
	PRODUCT_CAPACITY = Table::PRODUCT_CAPACITY,
	PRODUCT_CAPACITY_RESTRICTION = Table::PRODUCT_CAPACITY_RESTRICTION,
	EMPLOYEE_CHANGE = Table::EMPLOYEE_CHANGE,
	INTEGER,
	TEXT,
};

//table to str
extern const std::map<Table, std::string> TableToString;

extern const std::map<Type, std::string> TypeToString;

extern const std::map<std::string, Table> StringToTable;

//table to insertion query
extern const std::map<Table, std::string> TableToInsertionQuery;

extern const std::map<Table, std::string> TableToSelectionQuery;

extern const std::map<Table, std::string> TableToFilterQuery;

//table to the list of fields
//used for type checking / lookup
extern const std::map<Table, std::vector<std::pair<std::string, Type>>> TableToInsertionFields; 