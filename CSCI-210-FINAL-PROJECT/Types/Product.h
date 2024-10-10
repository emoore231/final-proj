#pragma once

#include <string>

#include "../property.h"

class AcquisitionContract;
class SalesContract;
class Transfer;
class Warehouse;
class ProductType;

class Product
{
private:
	void* Database;
	size_t ID;
	Product ();

public:
	Product (const size_t ID, void* Database);
	static Product New 
	(
		void* Database, 
		const AcquisitionContract&, 
		const SalesContract&, 
		const Transfer&, 
		const Warehouse&, 
		const ProductType&, 
		const std::string SerialNumber
	);

	void Delete ();

	property (AcquisitionContract, Product, ::AcquisitionContract);
	property (SalesContract, Product, ::SalesContract);
	property (Transfer, Product, ::Transfer);
	property (Warehouse, Product, ::Warehouse);
	property (ProductType, Product, ::ProductType);
};