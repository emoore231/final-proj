#include "Employee.h"

Employee::Employee (const size_t _ID, void* _Database) :
	Name (*this),
	SSN (*this),
	DOB (*this),
	Office (*this),
	Salary (*this),
	Schedule (*this),
	JobPosition (*this),
	Location (*this),
	Jurisdiction (*this),
	Manager (*this),

	ID(_ID),
	Database(_Database)
{}
