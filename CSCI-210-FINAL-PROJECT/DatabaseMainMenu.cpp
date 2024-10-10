#include "DatabaseMainMenu.h"

#include "SQLiteDB.h"
#include "global.h"

#include "DatabaseStandardEntryMenu.h"
#include "DatabaseAdvancedManipulationMenu.h"

bool DatabaseMainMenu ()
{
DISPLAY:
	//I call this the Moore Menu System
	const static std::vector<std::pair<int, std::pair<std::string, fptr_t>>> menuOptions = {
		{1, {"Exit application", [] () -> bool { return false; }}},
		{1, {"Standard data entry", DatabaseStandardEntryMenu }},
		{1, {"Generate database reports", nullptr }},
		{2, {"Generate advanced database reports", nullptr }},
		{3, {"Advanced data manipulation", DatabaseAdvancedManipulationMenu }},
		{4, {"User management", nullptr }},
		{5, {"Database administration", nullptr }},
	};

	std::cout << "Moore's C&R Central database" << lf
		<< "ACCESS LEVEL " << accessLevel << "." << lf;
	if (inTransaction)
		std::cout << "TRANSACTION IN PROGRESS" << lf << lf;
	std::cout << lf;

	std::cout << "Please select a menu option:" << lf;

	//print the menu options
	int i = 1;
	for (const auto menuOption : menuOptions)
		if (accessLevel >= menuOption.first)
			std::cout << '\t' << i++ << ": " << menuOption.second.first << std::endl;

	//get 'n call option
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