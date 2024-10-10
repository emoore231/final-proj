#include "DatabaseAdvancedManipulationMenu.h"
#include "DatabaseBeginTransactionMenu.h"
#include "DatabaseCommitTransactionMenu.h"
#include "DatabaseRollbackTransactionMenu.h"
#include "DatabaseInsertRecordIntoTableMenu.h"
#include <thread>
#include <string>
#include <iostream>
#include "SQLiteDB.h"
#include "global.h"

bool DatabaseAdvancedManipulationMenu ()
{
DISPLAY:

	const static std::vector<std::pair<int, std::pair<std::string, fptr_t>>> menuOptions = {
		{1, {"Return to previous menu", [] () -> bool { return false; }}},
		{3, {"Begin database transaction", DatabaseBeginTransactionMenu }},
		{3, {"Commit database transaction", DatabaseCommitTransactionMenu }},
		{3, {"Rollback database transaction", DatabaseRollbackTransactionMenu }},
		{3, {"Insert record into database", DatabaseInsertRecordIntoTableMenu }},
		{3, {"Update record in database", nullptr }},
		{3, {"Delete record from database", nullptr }},
		{3, {"Search records in database", nullptr }},
	};

	std::cout << "Moore's C&R Central database" << lf
		<< "ACCESS LEVEL " << accessLevel << "." << lf << lf;
	std::cout << "Moore's C&R Central database" << lf
		<< "ACCESS LEVEL " << accessLevel << "." << lf;
	if (inTransaction)
		std::cout << "TRANSACTION IN PROGRESS" << lf << lf;
	std::cout << lf;

	std::cout << "Please select a menu option:" << lf;

	int i = 1;
	for (const auto menuOption : menuOptions)
		if (accessLevel >= menuOption.first)
			std::cout << '\t' << i++ << ": " << menuOption.second.first << std::endl;

	try
	{
		std::cin >> std::ws >> i;
	}
	catch (...)
	{
		HandleIstreamFailure ();
		goto DISPLAY;
	}

	if (i > menuOptions.size () || i < 1)
		goto DISPLAY;
	else
		if (menuOptions[i - 1].second.second ())
			goto DISPLAY;
		else
			return true;
}