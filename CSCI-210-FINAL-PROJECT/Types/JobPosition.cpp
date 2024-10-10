#include "JobPosition.h"

JobPosition::JobPosition (const size_t _ID, void* _Database) :
	Name(*this),
	Description(*this),

	ID (_ID),
	Database (_Database)
{}