#include "EmployeeChange.h"

EmployeeChange::EmployeeChange (const size_t _ID, void* _Database) :
	Employee(*this),
	Manager(*this),
	Date(*this),
	Kind(*this),

	ID (_ID),
	Database (_Database)
{}
