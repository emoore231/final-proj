#include "Jurisdiction.h"

Jurisdiction::Jurisdiction (const size_t _ID, void* _Database) :
	State(*this),
	County(*this),
	City(*this),

	ID (_ID),
	Database (_Database)
{}
