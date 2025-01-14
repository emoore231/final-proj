/* Program name: main.cpp
*  Author: Evan Moore
*  Date last updated: 2024-03-30
* Purpose: Select rows from a database
*/

#include <iostream>
#include <setjmp.h> 
#include <thread>
#include "SQLiteDB.h" // the nice little library that makes this so simple
#include "main.h"
#include "global.h"

#include "DatabaseMainMenu.h"


//my old friend
jmp_buf jpr {};

//the access level of the user
extern int accessLevel {};
//if the database is in a transaction
extern bool inTransaction {};
//this is only allocated if there is a transaction
extern SQL::Transaction* currentTransactionDatabase {};
extern int currentTransactionOperationCount {};

typedef unsigned long long UINT64;

typedef struct
{
	UINT64 Address : 64;     
	UINT64 InMemory : 1;
	UINT64 Accessed : 1;
	UINT64 Modified : 1;

	UINT64 UserRead : 1;
	UINT64 UserWrite : 1;
	UINT64 UserExecute : 1;

} CustomPageTableEntry;

int main ()
{
	try
	{
		std::cin.exceptions (std::ios::badbit | std::ios::failbit | std::ios::eofbit);
		DatabaseLoginMenu ();
	}
	catch (const std::exception&)
	{
		std::cout << "A critical error has occured and the application has terminated.";
		exit (1);
	}
}

void DatabaseLoginMenu ()
{
	std::cout << "Welcome to Moore's C&R Management Solution" << lf
		<< '\t' << "Developed by the Senior Systems Engineer Director, Dr. Evan Moore" << lf
		<< '\t' << "WARNING: UNAUTHORIZED ACCESS IS STRICTLY PROHIBITED AND WILL GET YOU FIRED!" << lf << lf;

	std::cout << "ENTER USERNAME" << lf
		<< "The dev credentials are as usual, admin & password" << lf << lf;

ENTER_USERNAME:
	std::cout << "USERNAME: ";

	std::string username;

	std::cin >> std::ws >> username;

ENTER_PASSWORD:

	std::cout << "PASSWORD: ";

	std::string password;

	std::cin >> std::ws >> password;

	//std::this_thread::sleep_for (std::chrono::seconds (2));

	if (!(accessLevel = ValidateUserCredentials (username, password)))
	{
		std::cout << "INVALID CREDENTIALS" << lf;
		goto ENTER_USERNAME;
	}

	std::cout << "LOGIN SUCCESSFUL" << lf;
	//std::this_thread::sleep_for (std::chrono::seconds (2));
	DatabaseMainMenu ();
}

int ValidateUserCredentials (const std::string& username, const secure_string& password)
{
	return 5;
}

//global.h defs to put here

//table to str
extern const std::map<Table, std::string> TableToString {
	{Table::JURISDICTION,					"JURISDICTION"},
	{Table::LOCATION,						"LOCATION"},
	{Table::MANUFACTURER,					"MANUFACTURER"},
	{Table::SCHEDULE,						"SCHEDULE"},
	{Table::JOB_POSITION,					"JOB_POSITION"},
	{Table::PRODUCT_CATEGORY,				"PRODUCT_CATEGORY"},
	{Table::PRODUCT_TYPE,					"PRODUCT_TYPE"},
	{Table::REGULATION,						"REGULATION"},
	{Table::PURCHASER,						"PURCHASER"},
	{Table::SELLER,							"SELLER"},
	{Table::OFFICE,							"OFFICE"},
	{Table::EMPLOYEE,						"EMPLOYEE"},
	{Table::PRODUCT_REGULATION,				"PRODUCT_REGULATION"},
	{Table::WAREHOUSE,						"WAREHOUSE"},
	{Table::MANAGER,						"MANAGER"},
	{Table::MANAGEMENT,						"MANAGEMENT"},
	{Table::NEGOTIATER,						"NEGOTIATER"},
	{Table::SALES_CONTRACT,					"SALES_CONTRACT"},
	{Table::ACQUISITION_CONTRACT,			"ACQUISITION_CONTRACT"},
	{Table::PRODUCT,						"PRODUCT"},
	{Table::TRANSFER,						"TRANSFER"},
	{Table::PRODUCT_CAPACITY,				"PRODUCT_CAPACITY"},
	{Table::PRODUCT_CAPACITY_RESTRICTION,	"PRODUCT_CAPACITY_RESTRICTION"},
	{Table::EMPLOYEE_CHANGE,				"EMPLOYEE_CHANGE"},
};

extern const std::map<Type, std::string> TypeToString {
	{Type::INTEGER,							"INTEGER"},
	{Type::TEXT,							"TEXT"},
	{Type::JURISDICTION,					"JURISDICTION FOREIGN KEY"},
	{Type::LOCATION,						"LOCATION FOREIGN KEY"},
	{Type::MANUFACTURER,					"MANUFACTURER FOREIGN KEY"},
	{Type::SCHEDULE,						"SCHEDULE FOREIGN KEY"},
	{Type::JOB_POSITION,					"JOB_POSITION FOREIGN KEY"},
	{Type::PRODUCT_CATEGORY,				"PRODUCT_CATEGORY FOREIGN KEY"},
	{Type::PRODUCT_TYPE,					"PRODUCT_TYPE FOREIGN KEY"},
	{Type::REGULATION,						"REGULATION FOREIGN KEY"},
	{Type::PURCHASER,						"PURCHASER FOREIGN KEY"},
	{Type::SELLER,							"SELLER FOREIGN KEY"},
	{Type::OFFICE,							"OFFICE FOREIGN KEY"},
	{Type::EMPLOYEE,						"EMPLOYEE FOREIGN KEY"},
	{Type::PRODUCT_REGULATION,				"PRODUCT_REGULATION FOREIGN KEY"},
	{Type::WAREHOUSE,						"WAREHOUSE FOREIGN KEY"},
	{Type::MANAGER,							"MANAGER FOREIGN KEY"},
	{Type::MANAGEMENT,						"MANAGEMENT FOREIGN KEY"},
	{Type::NEGOTIATER,						"NEGOTIATER FOREIGN KEY"},
	{Type::SALES_CONTRACT,					"SALES_CONTRACT FOREIGN KEY"},
	{Type::ACQUISITION_CONTRACT,			"ACQUISITION_CONTRACT FOREIGN KEY"},
	{Type::PRODUCT,							"PRODUCT FOREIGN KEY"},
	{Type::TRANSFER,						"TRANSFER FOREIGN KEY"},
	{Type::PRODUCT_CAPACITY,				"PRODUCT_CAPACITY FOREIGN KEY"},
	{Type::PRODUCT_CAPACITY_RESTRICTION,	"PRODUCT_CAPACITY_RESTRICTION FOREIGN KEY"},
	{Type::EMPLOYEE_CHANGE,					"EMPLOYEE_CHANGE FOREIGN KEY"},
};

extern const std::map<std::string, Table> StringToTable {
	{"JURISDICTION",					Table::JURISDICTION},
	{"LOCATION",						Table::LOCATION},
	{"MANUFACTURER",					Table::MANUFACTURER},
	{"SCHEDULE",						Table::SCHEDULE},
	{"JOB_POSITION",					Table::JOB_POSITION},
	{"PRODUCT_CATEGORY",				Table::PRODUCT_CATEGORY},
	{"PRODUCT_TYPE",					Table::PRODUCT_TYPE},
	{"REGULATION",						Table::REGULATION},
	{"PURCHASER",						Table::PURCHASER},
	{"SELLER",							Table::SELLER},
	{"OFFICE",							Table::OFFICE},
	{"EMPLOYEE",						Table::EMPLOYEE},
	{"PRODUCT_REGULATION",				Table::PRODUCT_REGULATION},
	{"WAREHOUSE",						Table::WAREHOUSE},
	{"MANAGER",							Table::MANAGER},
	{"MANAGEMENT",						Table::MANAGEMENT},
	{"NEGOTIATER",						Table::NEGOTIATER},
	{"SALES_CONTRACT",					Table::SALES_CONTRACT},
	{"ACQUISITION_CONTRACT",			Table::ACQUISITION_CONTRACT},
	{"PRODUCT",							Table::PRODUCT},
	{"TRANSFER",						Table::TRANSFER},
	{"PRODUCT_CAPACITY",				Table::PRODUCT_CAPACITY},
	{"PRODUCT_CAPACITY_RESTRICTION",	Table::PRODUCT_CAPACITY_RESTRICTION},
	{"EMPLOYEE_CHANGE",					Table::EMPLOYEE_CHANGE},
};

//table to insertion query
extern const std::map<Table, std::string> TableToInsertionQuery {
	{Table::JURISDICTION,					R"(INSERT INTO JURISDICTION (STATE, COUNTY, CITY, ADDITIONAL) VALUES (?, ?, ?, ?);)"},
	{Table::LOCATION,						R"(INSERT INTO LOCATION (ADDR_LINE_1, ADDR_LINE_2, STATE, CITY, ZIP_CODE) VALUES (?, ?, ?, ?, ?);)"},
	{Table::MANUFACTURER,					R"(INSERT INTO MANUFACTURER (NAME, RELIABILITY) VALUES (?, ?);)"},
	{Table::SCHEDULE,						R"(INSERT INTO SCHEDULE (M_START_HR, M_END_HR, T_START_HR, T_END_HR, W_START_HR, W_END_HR, TH_START_HR, TH_END_HR, F_START_HR, F_END_HR, S_START_HR, S_END_HR) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);)"},
	{Table::JOB_POSITION,					R"(INSERT INTO JOB_POSITION (NAME, DESCRIPTION) VALUES (?, ?);)"},
	{Table::PRODUCT_CATEGORY,				R"(INSERT INTO PRODUCT_CATEGORY (NAME, DESCRIPTION) VALUES (?, ?);)"},
	{Table::PRODUCT_TYPE,					R"(INSERT INTO PRODUCT_TYPE (MANUFACTURER_ID, PRODUCT_CATEGORY_ID, NAME, DESCRIPTION, DEMAND_INDEX) VALUES (?, ?, ?, ?, ?);)"},
	{Table::REGULATION,						R"(INSERT INTO REGULATION (JURISDICTION_ID, LEGAL_CODE, AUTHORING_BODY) VALUES (?, ?, ?);)"},
	{Table::PURCHASER,						R"(INSERT INTO PURCHASER (JURISDICTION_ID, NAME, KIND, TELEPHONE, NRA_NUMBER, DLN_NUMBER, ATF_NUMBER) VALUES (?, ?, ?, ?, ?, ?, ?);)"},
	{Table::SELLER,							R"(INSERT INTO SELLER (JURISDICTION_ID, NAME, RELIABILITY) VALUES (?, ?, ?);)"},
	{Table::OFFICE,							R"(INSERT INTO OFFICE (LOCATION_ID, JURISDICTION_ID) VALUES (?, ?);)"},
	{Table::EMPLOYEE,						R"(INSERT INTO EMPLOYEE (NAME, SSN, DOB, SALARY, OFFICE_ID, SCHEDULE_ID, JOB_POSITION_ID, LOCATION_ID, JURISDICTION_ID) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?);)"},
	{Table::PRODUCT_REGULATION,				R"(INSERT INTO PRODUCT_REGULATION (PRODUCT_CATEGORY_ID, REGULATION_ID) VALUES (?, ?);)"},
	{Table::WAREHOUSE,						R"(INSERT INTO WAREHOUSE (OFFICE_ID, SIZE_TYPE) VALUES (?, ?);)"},
	{Table::MANAGER,						R"(INSERT INTO MANAGER (NOTES, EMPLOYEE_ID, AUTHORITY_LEVEL) VALUES (?, ?, ?);)"},
	{Table::MANAGEMENT,						R"(INSERT INTO MANAGEMENT (MANAGER_ID, EMPLOYEE_ID) VALUES (?, ?);)"},
	{Table::NEGOTIATER,						R"(INSERT INTO NEGOTIATER (EMPLOYEE_ID, FAVORIBILITY, NOTES) VALUES (?, ?, ?);)"},
	{Table::SALES_CONTRACT,					R"(INSERT INTO SALES_CONTRACT (PURCHASER_ID, JURISDICTION_ID, NEGOTIATER_ID, MANAGER_ID, GRAND_TOTAL, DATE) VALUES (?, ?, ?, ?, ?, ?);)"},
	{Table::ACQUISITION_CONTRACT,			R"(INSERT INTO ACQUISITION_CONTRACT (PURCHASER_ID, JURISDICTION_ID, NEGOTIATER_ID, MANAGER_ID, GRAND_TOTAL, DATE) VALUES (?, ?, ?, ?, ?, ?);)"},
	{Table::PRODUCT,						R"(INSERT INTO PRODUCT (ACQUISITION_CONTRACT_ID, SALES_CONTRACT_ID, WAREHOUSE_ID, PRODUCT_TYPE_ID, SERIAL_NUMBER) VALUES (?, ?, ?, ?, ?);)"},
	{Table::TRANSFER,						R"(INSERT INTO TRANSFER (WAREHOUSE_ORIGIN_ID, WAREHOUSE_DESTINATION_ID, PRODUCT_ID, MANAGER_ID, DATE) VALUES (?, ?, ?, ?, ?);)"},
	{Table::PRODUCT_CAPACITY,				R"(INSERT INTO PRODUCT_CAPACITY (WAREHOUSE_ID, PRODUCT_TYPE_ID) VALUES (?, ?);)"},
	{Table::PRODUCT_CAPACITY_RESTRICTION,	R"(INSERT INTO PRODUCT_CAPACITY_RESTRICTION (PRODUCT_CAPACITY_ID, MAX_CAPACITY, RESTRICTIONS) VALUES (?, ?, ?);)"},
	{Table::EMPLOYEE_CHANGE,				R"(INSERT INTO EMPLOYEE_CHANGE (EMPLOYEE_ID, MANAGER_ID, DATE, KIND) VALUES (?, ?, ?, ?);)"},
};

extern const std::map<Table, std::string> TableToUpdateQuery {
	{Table::JURISDICTION,                		R"(UPDATE JURISDICTION SET STATE = ?, COUNTY = ?, CITY = ?, ADDITIONAL = ? WHERE ID = ?;)"},
	{Table::LOCATION,                			R"(UPDATE LOCATION SET ADDR_LINE_1 = ?, ADDR_LINE_2 = ?, STATE = ?, CITY = ?, ZIP_CODE = ? WHERE ID = ?;)"},
	{Table::MANUFACTURER,                		R"(UPDATE MANUFACTURER SET NAME = ?, RELIABILITY = ? WHERE ID = ?;)"},
	{Table::SCHEDULE,                			R"(UPDATE SCHEDULE SET M_START_HR = ?, M_END_HR = ?, T_START_HR = ?, T_END_HR = ?, W_START_HR = ?, W_END_HR = ?, TH_START_HR = ?, TH_END_HR = ?, F_START_HR = ?, F_END_HR = ?, S_START_HR = ?, S_END_HR = ?} {WHERE ID = ?;)"},
	{Table::JOB_POSITION,                		R"(UPDATE JOB_POSITION SET NAME = ?, DESCRIPTION = ? WHERE ID = ?;)"},
	{Table::PRODUCT_CATEGORY,                	R"(UPDATE PRODUCT_CATEGORY SET NAME = ?, DESCRIPTION = ? WHERE ID = ?;)"},
	{Table::PRODUCT_TYPE,                		R"(UPDATE PRODUCT_TYPE SET MANUFACTURER_ID = ?, PRODUCT_CATEGORY_ID = ?, NAME = ?, DESCRIPTION = ?, DEMAND_INDEX = ? WHERE ID = ?;)"},
	{Table::REGULATION,              			R"(UPDATE REGULATION SET JURISDICTION_ID = ?, LEGAL_CODE = ?, AUTHORING_BODY = ? WHERE ID = ?;)"},
	{Table::PURCHASER,               			R"(UPDATE PURCHASER SET JURISDICTION_ID = ?, NAME = ?, KIND = ?, TELEPHONE = ?, NRA_NUMBER = ?, DLN_NUMBER = ?, ATF_NUMBER = ? WHERE ID = ?;)"},
	{Table::SELLER,              				R"(UPDATE SELLER SET JURISDICTION_ID = ?, NAME = ?, RELIABILITY = ? WHERE ID = ?;)"},
	{Table::OFFICE,              				R"(UPDATE OFFICE SET LOCATION_ID = ?, JURISDICTION_ID = ? WHERE ID = ?;)"},
	{Table::EMPLOYEE,                			R"(UPDATE EMPLOYEE SET NAME = ?, SSN = ?, DOB = ?, SALARY = ?, OFFICE_ID = ?, SCHEDULE_ID = ?, JOB_POSITION_ID = ?, LOCATION_ID = ?, JURISDICTION_ID = ? WHERE ID = ?;)"},
	{Table::PRODUCT_REGULATION,              	R"(UPDATE PRODUCT_REGULATION SET PRODUCT_CATEGORY_ID = ?, REGULATION_ID = ? WHERE ID = ?;)"},
	{Table::WAREHOUSE,               			R"(UPDATE WAREHOUSE SET OFFICE_ID = ?, SIZE_TYPE = ? WHERE ID = ?;)"},
	{Table::MANAGER,             				R"(UPDATE MANAGER SET NOTES = ?, EMPLOYEE_ID = ?, AUTHORITY_LEVEL = ? WHERE ID = ?;)"},
	{Table::MANAGEMENT,              			R"(UPDATE MANAGEMENT SET MANAGER_ID = ?, EMPLOYEE_ID = ? WHERE ID = ?;)"},
	{Table::NEGOTIATER,              			R"(UPDATE NEGOTIATER SET EMPLOYEE_ID = ?, FAVORIBILITY = ?, NOTES = ? WHERE ID = ?;)"},
	{Table::SALES_CONTRACT,              		R"(UPDATE SALES_CONTRACT SET PURCHASER_ID = ?, JURISDICTION_ID = ?, NEGOTIATER_ID = ?, MANAGER_ID = ?, GRAND_TOTAL = ?, DATE = ? WHERE ID = ?;)"},
	{Table::ACQUISITION_CONTRACT,            	R"(UPDATE ACQUISITION_CONTRACT SET PURCHASER_ID = ?, JURISDICTION_ID = ?, NEGOTIATER_ID = ?, MANAGER_ID = ?, GRAND_TOTAL = ?, DATE = ? WHERE ID = ?;)"},
	{Table::PRODUCT,             				R"(UPDATE PRODUCT SET ACQUISITION_CONTRACT_ID = ?, SALES_CONTRACT_ID = ?, WAREHOUSE_ID = ?, PRODUCT_TYPE_ID = ?, SERIAL_NUMBER = ? WHERE ID = ?;)"},
	{Table::TRANSFER,                			R"(UPDATE TRANSFER SET WAREHOUSE_ORIGIN_ID = ?, WAREHOUSE_DESTINATION_ID = ?, PRODUCT_ID = ?, MANAGER_ID = ?, DATE = ? WHERE ID = ?;)"},
	{Table::PRODUCT_CAPACITY,                	R"(UPDATE PRODUCT_CAPACITY SET WAREHOUSE_ID = ?, PRODUCT_TYPE_ID = ? WHERE ID = ?;)"},
	{Table::PRODUCT_CAPACITY_RESTRICTION,    	R"(UPDATE PRODUCT_CAPACITY_RESTRICTION SET PRODUCT_CAPACITY_ID = ?, MAX_CAPACITY = ?, RESTRICTIONS = ? WHERE ID = ?;)"},
	{Table::EMPLOYEE_CHANGE,             		R"(UPDATE EMPLOYEE_CHANGE SET EMPLOYEE_ID = ?, MANAGER_ID = ?, DATE = ?, KIND = ? WHERE ID = ?;)"},
};

extern const std::map<Table, std::string> TableToSelectionQuery {
	{Table::JURISDICTION,					R"(SELECT * FROM JURISDICTION;)"},
	{Table::LOCATION,						R"(SELECT * FROM LOCATION;)"},
	{Table::MANUFACTURER,					R"(SELECT * FROM MANUFACTURER;)"},
	{Table::SCHEDULE,						R"(SELECT * FROM SCHEDULE;)"},
	{Table::JOB_POSITION,					R"(SELECT * FROM JOB_POSITION;)"},
	{Table::PRODUCT_CATEGORY,				R"(SELECT * FROM PRODUCT_CATEGORY;)"},
	{Table::PRODUCT_TYPE,					R"(SELECT * FROM PRODUCT_TYPE;)"},
	{Table::REGULATION,						R"(SELECT * FROM REGULATION;)"},
	{Table::PURCHASER,						R"(SELECT * FROM PURCHASER;)"},
	{Table::SELLER,							R"(SELECT * FROM SELLER;)"},
	{Table::OFFICE,							R"(SELECT * FROM OFFICE;)"},
	{Table::EMPLOYEE,						R"(SELECT * FROM EMPLOYEE;)"},
	{Table::PRODUCT_REGULATION,				R"(SELECT * FROM PRODUCT_REGULATION;)"},
	{Table::WAREHOUSE,						R"(SELECT * FROM WAREHOUSE;)"},
	{Table::MANAGER,						R"(SELECT * FROM MANAGER;)"},
	{Table::MANAGEMENT,						R"(SELECT * FROM MANAGEMENT;)"},
	{Table::NEGOTIATER,						R"(SELECT * FROM NEGOTIATER;)"},
	{Table::SALES_CONTRACT,					R"(SELECT * FROM SALES_CONTRACT;)"},
	{Table::ACQUISITION_CONTRACT,			R"(SELECT * FROM ACQUISITION_CONTRACT;)"},
	{Table::PRODUCT,						R"(SELECT * FROM PRODUCT;)"},
	{Table::TRANSFER,						R"(SELECT * FROM TRANSFER;)"},
	{Table::PRODUCT_CAPACITY,				R"(SELECT * FROM PRODUCT_CAPACITY;)"},
	{Table::PRODUCT_CAPACITY_RESTRICTION,	R"(SELECT * FROM PRODUCT_CAPACITY_RESTRICTION;)"},
	{Table::EMPLOYEE_CHANGE,				R"(SELECT * FROM EMPLOYEE_CHANGE;)"},
};

extern const std::map<Table, std::string> TableToFilterQuery {
	{Table::JURISDICTION,					R"(SELECT * FROM JURISDICTION WHERE (STATE LIKE ? OR ? IS NULL) AND (COUNTY LIKE ? OR ? IS NULL) AND (CITY LIKE ? OR ? IS NULL) AND (ADDITIONAL LIKE ? OR ? IS NULL));)"},
	{Table::LOCATION,						R"(SELECT * FROM LOCATION WHERE (ADDR_LINE_1 LIKE ? OR ? IS NULL) AND (ADDR_LINE_2 LIKE ? OR ? IS NULL) AND (STATE LIKE ? OR ? IS NULL) AND (CITY LIKE ? OR ? IS NULL) AND (ZIP_CODE LIKE ? OR ? IS NULL));)"},
	{Table::MANUFACTURER,					R"(SELECT * FROM MANUFACTURER WHERE (NAME LIKE ? OR ? IS NULL) AND (RELIABILITY LIKE ? OR ? IS NULL));)"},
	{Table::SCHEDULE,						R"(SELECT * FROM SCHEDULE WHERE (M_START_HR LIKE ? OR ? IS NULL) AND (M_END_HR LIKE ? OR ? IS NULL) AND (T_START_HR LIKE ? OR ? IS NULL) AND (T_END_HR LIKE ? OR ? IS NULL) AND (W_START_HR LIKE ? OR ? IS NULL) AND (W_END_HR LIKE ? OR ? IS NULL) AND (TH_START_HR LIKE ? OR ? IS NULL) AND (TH_END_HR LIKE ? OR ? IS NULL) AND (F_START_HR LIKE ? OR ? IS NULL) AND (F_END_HR LIKE ? OR ? IS NULL) AND (S_START_HR LIKE ? OR ? IS NULL) AND (S_END_HR LIKE ? OR ? IS NULL));)"},
	{Table::JOB_POSITION,					R"(SELECT * FROM JOB_POSITION WHERE (NAME LIKE ? OR ? IS NULL) AND (DESCRIPTION LIKE ? OR ? IS NULL));)"},
	{Table::PRODUCT_CATEGORY,				R"(SELECT * FROM PRODUCT_CATEGORY WHERE (NAME LIKE ? OR ? IS NULL) AND (DESCRIPTION LIKE ? OR ? IS NULL));)"},
	{Table::PRODUCT_TYPE,					R"(SELECT * FROM PRODUCT_TYPE WHERE (MANUFACTURER_ID LIKE ? OR ? IS NULL) AND (PRODUCT_CATEGORY_ID LIKE ? OR ? IS NULL) AND (NAME LIKE ? OR ? IS NULL) AND (DESCRIPTION LIKE ? OR ? IS NULL) AND (DEMAND_INDEX LIKE ? OR ? IS NULL));)"},
	{Table::REGULATION,						R"(SELECT * FROM REGULATION WHERE (JURISDICTION_ID LIKE ? OR ? IS NULL) AND (LEGAL_CODE LIKE ? OR ? IS NULL) AND (AUTHORING_BODY LIKE ? OR ? IS NULL));)"},
	{Table::PURCHASER,						R"(SELECT * FROM PURCHASER WHERE (JURISDICTION_ID LIKE ? OR ? IS NULL) AND (NAME LIKE ? OR ? IS NULL) AND (KIND LIKE ? OR ? IS NULL) AND (TELEPHONE LIKE ? OR ? IS NULL) AND (NRA_NUMBER LIKE ? OR ? IS NULL) AND (DLN_NUMBER LIKE ? OR ? IS NULL) AND (ATF_NUMBER LIKE ? OR ? IS NULL));)"},
	{Table::SELLER,							R"(SELECT * FROM SELLER WHERE (JURISDICTION_ID LIKE ? OR ? IS NULL) AND (NAME LIKE ? OR ? IS NULL) AND (RELIABILITY LIKE ? OR ? IS NULL));)"},
	{Table::OFFICE,							R"(SELECT * FROM OFFICE WHERE (LOCATION_ID LIKE ? OR ? IS NULL) AND (JURISDICTION_ID LIKE ? OR ? IS NULL));)"},
	{Table::EMPLOYEE,						R"(SELECT * FROM EMPLOYEE WHERE (NAME LIKE ? OR ? IS NULL) AND (SSN LIKE ? OR ? IS NULL) AND (DOB LIKE ? OR ? IS NULL) AND (SALARY LIKE ? OR ? IS NULL) AND (OFFICE_ID LIKE ? OR ? IS NULL) AND (SCHEDULE_ID LIKE ? OR ? IS NULL) AND (JOB_POSITION_ID LIKE ? OR ? IS NULL) AND (LOCATION_ID LIKE ? OR ? IS NULL) AND (JURISDICTION_ID LIKE ? OR ? IS NULL));)"},
	{Table::PRODUCT_REGULATION,				R"(SELECT * FROM PRODUCT_REGULATION WHERE (PRODUCT_CATEGORY_ID LIKE ? OR ? IS NULL) AND (REGULATION_ID LIKE ? OR ? IS NULL));)"},
	{Table::WAREHOUSE,						R"(SELECT * FROM WAREHOUSE WHERE (OFFICE_ID LIKE ? OR ? IS NULL) AND (SIZE_TYPE LIKE ? OR ? IS NULL));)"},
	{Table::MANAGER,						R"(SELECT * FROM MANAGER WHERE (NOTES LIKE ? OR ? IS NULL) AND (EMPLOYEE_ID LIKE ? OR ? IS NULL) AND (AUTHORITY_LEVEL LIKE ? OR ? IS NULL));)"},
	{Table::MANAGEMENT,						R"(SELECT * FROM MANAGEMENT WHERE (MANAGER_ID LIKE ? OR ? IS NULL) AND (EMPLOYEE_ID LIKE ? OR ? IS NULL));)"},
	{Table::NEGOTIATER,						R"(SELECT * FROM NEGOTIATER WHERE (EMPLOYEE_ID LIKE ? OR ? IS NULL) AND (FAVORIBILITY LIKE ? OR ? IS NULL) AND (NOTES LIKE ? OR ? IS NULL));)"},
	{Table::SALES_CONTRACT,					R"(SELECT * FROM SALES_CONTRACT WHERE (PURCHASER_ID LIKE ? OR ? IS NULL) AND (JURISDICTION_ID LIKE ? OR ? IS NULL) AND (NEGOTIATER_ID LIKE ? OR ? IS NULL) AND (MANAGER_ID LIKE ? OR ? IS NULL) AND (GRAND_TOTAL LIKE ? OR ? IS NULL) AND (DATE LIKE ? OR ? IS NULL));)"},
	{Table::ACQUISITION_CONTRACT,			R"(SELECT * FROM ACQUISITION_CONTRACT WHERE (PURCHASER_ID LIKE ? OR ? IS NULL) AND (JURISDICTION_ID LIKE ? OR ? IS NULL) AND (NEGOTIATER_ID LIKE ? OR ? IS NULL) AND (MANAGER_ID LIKE ? OR ? IS NULL) AND (GRAND_TOTAL LIKE ? OR ? IS NULL) AND (DATE LIKE ? OR ? IS NULL));)"},
	{Table::PRODUCT,						R"(SELECT * FROM PRODUCT WHERE (ACQUISITION_CONTRACT_ID LIKE ? OR ? IS NULL) AND (SALES_CONTRACT_ID LIKE ? OR ? IS NULL) AND (WAREHOUSE_ID LIKE ? OR ? IS NULL) AND (PRODUCT_TYPE_ID LIKE ? OR ? IS NULL) AND (SERIAL_NUMBER LIKE ? OR ? IS NULL));)"},
	{Table::TRANSFER,						R"(SELECT * FROM TRANSFER WHERE (WAREHOUSE_ORIGIN_ID LIKE ? OR ? IS NULL) AND (WAREHOUSE_DESTINATION_ID LIKE ? OR ? IS NULL) AND (PRODUCT_ID LIKE ? OR ? IS NULL) AND (MANAGER_ID LIKE ? OR ? IS NULL) AND (DATE LIKE ? OR ? IS NULL));)"},
	{Table::PRODUCT_CAPACITY,				R"(SELECT * FROM PRODUCT_CAPACITY WHERE (WAREHOUSE_ID LIKE ? OR ? IS NULL) AND (PRODUCT_TYPE_ID LIKE ? OR ? IS NULL));)"},
	{Table::PRODUCT_CAPACITY_RESTRICTION,	R"(SELECT * FROM PRODUCT_CAPACITY_RESTRICTION WHERE (PRODUCT_CAPACITY_ID LIKE ? OR ? IS NULL) AND (MAX_CAPACITY LIKE ? OR ? IS NULL) AND (RESTRICTIONS LIKE ? OR ? IS NULL));)"},
	{Table::EMPLOYEE_CHANGE,				R"(SELECT * FROM EMPLOYEE_CHANGE WHERE (EMPLOYEE_ID LIKE ? OR ? IS NULL) AND (MANAGER_ID LIKE ? OR ? IS NULL) AND (DATE LIKE ? OR ? IS NULL) AND (KIND LIKE ? OR ? IS NULL));)"},
};

//table to the list of fields
//used for type checking / lookup
extern const std::map<Table, std::vector<std::pair<std::string, Type>>> TableToInsertionFields
{
	{Table::JURISDICTION, {{"STATE", Type::TEXT}, {"COUNTY", Type::TEXT}, {"CITY", Type::TEXT}, {"ADDITIONAL", Type::TEXT}}},
	{Table::LOCATION, {{"ADDR_LINE_1", Type::TEXT}, {"ADDR_LINE_2", Type::TEXT}, {"STATE", Type::TEXT}, {"CITY", Type::TEXT}, {"ZIP_CODE", Type::TEXT}}},
	{Table::MANUFACTURER, {{"NAME", Type::TEXT}, {"RELIABILITY", Type::INTEGER}}},
	{Table::SCHEDULE, {{"M_START_HR", Type::INTEGER}, {"M_END_HR", Type::INTEGER}, {"T_START_HR", Type::INTEGER}, {"T_END_HR", Type::INTEGER},
					   {"W_START_HR", Type::INTEGER}, {"W_END_HR", Type::INTEGER}, {"TH_START_HR", Type::INTEGER}, {"TH_END_HR", Type::INTEGER},
					   {"F_START_HR", Type::INTEGER}, {"F_END_HR", Type::INTEGER}, {"S_START_HR", Type::INTEGER}, {"S_END_HR", Type::INTEGER}}},
	{Table::JOB_POSITION, {{"NAME", Type::TEXT}, {"DESCRIPTION", Type::TEXT}}},
	{Table::PRODUCT_CATEGORY, {{"NAME", Type::TEXT}, {"DESCRIPTION", Type::TEXT}}},
	{Table::PRODUCT_TYPE, {{"MANUFACTURER_ID", Type::MANUFACTURER}, {"PRODUCT_CATEGORY_ID", Type::PRODUCT_CATEGORY}, {"NAME", Type::TEXT}, {"DESCRIPTION", Type::TEXT}, {"DEMAND_INDEX", Type::INTEGER}}},
	{Table::REGULATION, {{"JURISDICTION_ID", Type::JURISDICTION}, {"LEGAL_CODE", Type::TEXT}, {"AUTHORING_BODY", Type::TEXT}}},
	{Table::PURCHASER, {{"JURISDICTION_ID", Type::JURISDICTION}, {"NAME", Type::TEXT}, {"KIND", Type::TEXT}, {"TELEPHONE", Type::TEXT}, {"NRA_NUMBER", Type::TEXT}, {"DLN_NUMBER", Type::TEXT}, {"ATF_NUMBER", Type::TEXT}}},
	{Table::SELLER, {{"JURISDICTION_ID", Type::JURISDICTION}, {"NAME", Type::TEXT}, {"RELIABILITY", Type::INTEGER}}},
	{Table::OFFICE, {{"LOCATION_ID", Type::LOCATION}, {"JURISDICTION_ID", Type::JURISDICTION}}},
	{Table::EMPLOYEE, {{"NAME", Type::TEXT}, {"SSN", Type::TEXT}, {"DOB", Type::TEXT}, {"SALARY", Type::INTEGER}, {"OFFICE_ID", Type::OFFICE}, {"SCHEDULE_ID", Type::SCHEDULE}, {"JOB_POSITION_ID", Type::JOB_POSITION}, {"LOCATION_ID", Type::LOCATION}, {"JURISDICTION_ID", Type::JURISDICTION}}},
	{Table::PRODUCT_REGULATION, {{"PRODUCT_CATEGORY_ID", Type::PRODUCT_CATEGORY}, {"REGULATION_ID", Type::REGULATION}}},
	{Table::WAREHOUSE, {{"OFFICE_ID", Type::OFFICE}, {"SIZE_TYPE", Type::TEXT}}},
	{Table::MANAGER, {{"NOTES", Type::TEXT}, {"EMPLOYEE_ID", Type::EMPLOYEE}, {"AUTHORITY_LEVEL", Type::TEXT}}},
	{Table::MANAGEMENT, {{"MANAGER_ID", Type::MANAGER}, {"EMPLOYEE_ID", Type::EMPLOYEE}}},
	{Table::NEGOTIATER, {{"EMPLOYEE_ID", Type::EMPLOYEE}, {"FAVORIBILITY", Type::TEXT}, {"NOTES", Type::TEXT}}},
	{Table::SALES_CONTRACT, {{"PURCHASER_ID", Type::PURCHASER}, {"JURISDICTION_ID", Type::JURISDICTION}, {"NEGOTIATER_ID", Type::NEGOTIATER}, {"MANAGER_ID", Type::MANAGER}, {"GRAND_TOTAL", Type::INTEGER}, {"DATE", Type::INTEGER}}},
	{Table::ACQUISITION_CONTRACT, {{"PURCHASER_ID", Type::PURCHASER}, {"JURISDICTION_ID", Type::JURISDICTION}, {"NEGOTIATER_ID", Type::NEGOTIATER}, {"MANAGER_ID", Type::MANAGER}, {"GRAND_TOTAL", Type::INTEGER}, {"DATE", Type::INTEGER}}},
	{Table::PRODUCT, {{"ACQUISITION_CONTRACT_ID", Type::ACQUISITION_CONTRACT}, {"SALES_CONTRACT_ID", Type::SALES_CONTRACT}, {"WAREHOUSE_ID", Type::WAREHOUSE}, {"PRODUCT_TYPE_ID", Type::PRODUCT_TYPE}, {"SERIAL_NUMBER", Type::TEXT}}},
	{Table::TRANSFER, {{"WAREHOUSE_ORIGIN_ID", Type::WAREHOUSE}, {"WAREHOUSE_DESTINATION_ID", Type::WAREHOUSE}, {"PRODUCT_ID", Type::PRODUCT}, {"MANAGER_ID", Type::MANAGER}, {"DATE", Type::INTEGER}}},
	{Table::PRODUCT_CAPACITY, {{"WAREHOUSE_ID", Type::WAREHOUSE}, {"PRODUCT_TYPE_ID", Type::PRODUCT_TYPE}}},
	{Table::PRODUCT_CAPACITY_RESTRICTION, {{"PRODUCT_CAPACITY_ID", Type::PRODUCT_CAPACITY}, {"MAX_CAPACITY", Type::INTEGER}, {"RESTRICTIONS", Type::TEXT}}},
	{Table::EMPLOYEE_CHANGE, {{"EMPLOYEE_ID", Type::EMPLOYEE}, {"MANAGER_ID", Type::MANAGER}, {"DATE", Type::INTEGER}, {"KIND", Type::TEXT}}},
};

extern const std::map<Table, std::string> TableToDeleteQuery {
	{Table::JURISDICTION,					R"(DELETE FROM JURISDICTION WHERE ID=?;)"},
	{Table::LOCATION,						R"(DELETE FROM LOCATION WHERE ID=?;)"},
	{Table::MANUFACTURER,					R"(DELETE FROM MANUFACTURER WHERE ID=?;)"},
	{Table::SCHEDULE,						R"(DELETE FROM SCHEDULE WHERE ID=?;)"},
	{Table::JOB_POSITION,					R"(DELETE FROM JOB_POSITION WHERE ID=?;)"},
	{Table::PRODUCT_CATEGORY,				R"(DELETE FROM PRODUCT_CATEGORY WHERE ID=?;)"},
	{Table::PRODUCT_TYPE,					R"(DELETE FROM PRODUCT_TYPE WHERE ID=?;)"},
	{Table::REGULATION,						R"(DELETE FROM REGULATION WHERE ID=?;)"},
	{Table::PURCHASER,						R"(DELETE FROM PURCHASER WHERE ID=?;)"},
	{Table::SELLER,							R"(DELETE FROM SELLER WHERE ID=?;)"},
	{Table::OFFICE,							R"(DELETE FROM OFFICE WHERE ID=?;)"},
	{Table::EMPLOYEE,						R"(DELETE FROM EMPLOYEE WHERE ID=?;)"},
	{Table::PRODUCT_REGULATION,				R"(DELETE FROM PRODUCT_REGULATION WHERE ID=?;)"},
	{Table::WAREHOUSE,						R"(DELETE FROM WAREHOUSE WHERE ID=?;)"},
	{Table::MANAGER,						R"(DELETE FROM MANAGER WHERE ID=?;)"},
	{Table::MANAGEMENT,						R"(DELETE FROM MANAGEMENT WHERE ID=?;)"},
	{Table::NEGOTIATER,						R"(DELETE FROM NEGOTIATER WHERE ID=?;)"},
	{Table::SALES_CONTRACT,					R"(DELETE FROM SALES_CONTRACT WHERE ID=?;)"},
	{Table::ACQUISITION_CONTRACT,			R"(DELETE FROM ACQUISITION_CONTRACT WHERE ID=?;)"},
	{Table::PRODUCT,						R"(DELETE FROM PRODUCT WHERE ID=?;)"},
	{Table::TRANSFER,						R"(DELETE FROM TRANSFER WHERE ID=?;)"},
	{Table::PRODUCT_CAPACITY,				R"(DELETE FROM PRODUCT_CAPACITY WHERE ID=?;)"},
	{Table::PRODUCT_CAPACITY_RESTRICTION,	R"(DELETE FROM PRODUCT_CAPACITY_RESTRICTION WHERE ID=?;)"},
	{Table::EMPLOYEE_CHANGE,				R"(DELETE FROM EMPLOYEE_CHANGE WHERE ID=?;)"},
};