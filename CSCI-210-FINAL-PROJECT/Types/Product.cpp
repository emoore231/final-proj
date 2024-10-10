#include "Product.h"

#include "../MasterDB.h"

#include "AcquisitionContract.h"
#include "SalesContract.h"
#include "Transfer.h"
#include "Warehouse.h"
#include "ProductType.h"

Product::Product () :
	AcquisitionContract (*this),
	SalesContract (*this),
	Transfer (*this),
	Warehouse (*this),
	ProductType (*this)
{}

Product::Product (const size_t iD, void* database) :
	AcquisitionContract (*this),
	SalesContract (*this),
	Transfer (*this),
	Warehouse (*this),
	ProductType (*this),

	ID (iD),
	Database (database)
{}

Product Product::New
(
	void* Database,
	const ::AcquisitionContract& _AcquisitionContract,
	const ::SalesContract& _SalesContract,
	const ::Transfer& _Transfer,
	const ::Warehouse& _Warehouse,
	const ::ProductType& _ProductType,
	const std::string SerialNumber
)
{
	Product Inst {};
	((SQL::Database*)Database)->ExecuteParameterized (R"(INSERT INTO PRODUCTS VALUES (?, ?, ?, ?, ?, ?, ?);)",
													  {
														  std::to_string (Inst.ID = rand ()),//just generate random rather than use sequential
														  std::to_string (_AcquisitionContract.ID),
														  std::to_string (_SalesContract.ID),
														  std::to_string (_Transfer.ID),
														  std::to_string (_Warehouse.ID),
														  std::to_string (_ProductType.ID),
														  SerialNumber
													  });
	return Inst;
}

void Product::Delete ()
{
	((SQL::Database*)Database)->ExecuteParameterized (R"(DELETE FROM PRODUCTS WHERE ID = ?;)",
													  {
														  std::to_string (ID)
													  });
	this->~Product ();
}

const AcquisitionContract Product::AcquisitionContractProperty::get () const
{
	auto Res = ((SQL::Database*)prop::ref.Database)->ExecuteParameterized (R"(SELECT ACQUISITION_CONTRACT_ID FROM PRODUCTS WHERE ID = ?)",
													  {
														   std::to_string (prop::ref.ID)
													  });

	if (!Res.HasData)
		throw std::runtime_error ("DATA NOT FOUND");
	else
		return ::AcquisitionContract((size_t)atol(Res.Data["ACQUISITION_CONTRACT_ID"][0].c_str()), prop::ref.Database);
}

void Product::AcquisitionContractProperty::set (const ::AcquisitionContract& rhs)
{

}