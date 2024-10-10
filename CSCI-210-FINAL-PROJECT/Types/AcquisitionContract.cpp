#include "AcquisitionContract.h"

AcquisitionContract::AcquisitionContract (const size_t _ID, void* _Database) :
	Seller(*this),
	Jurisdiction(*this),
	Negotiater (*this),
	Manager (*this),
	GrandTotal (*this),
	Date (*this),

	ID(_ID),
	Database(_Database)
{}