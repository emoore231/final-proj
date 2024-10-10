#include "Schedule.h"

#include "../SQLiteDB.h"

inline Schedule::Schedule () :
	MondayStartHour (*this),
	MondayEndHour (*this),
	TuesdayStartHour (*this),
	TuesdayEndHour (*this),
	WendsdayStartHour (*this),
	WendsdayEndHour (*this),
	ThursdayStartHour (*this),
	ThursdayEndHour (*this),
	FridayStartHour (*this),
	FridayEndHour (*this),
	SaturdayStartHour (*this),
	SaturdayEndHour (*this)
{}

Schedule::Schedule (const size_t _ID, void* _Database) :
	MondayStartHour(*this),
	MondayEndHour(*this),
	TuesdayStartHour(*this),
	TuesdayEndHour(*this),
	WendsdayStartHour(*this),
	WendsdayEndHour(*this),
	ThursdayStartHour(*this),
	ThursdayEndHour(*this),
	FridayStartHour(*this),
	FridayEndHour(*this),
	SaturdayStartHour(*this),
	SaturdayEndHour(*this),

	ID (_ID),
	Database (_Database)
{}

Schedule Schedule::New 
(
	void* Database,
	const size_t MondayStartHour,
	const size_t MondayEndHour,
	const size_t TuesdayStartHour,
	const size_t TuesdayEndHour,
	const size_t WendsdayStartHour,
	const size_t WendsdayEndHour,
	const size_t ThursdayStartHour,
	const size_t ThursdayEndHour,
	const size_t FridayStartHour,
	const size_t FridayEndHour,
	const size_t SaturdayStartHour,
	const size_t SaturdayEndHour
)
{
	Schedule Inst {};
	Inst.Database = Database;
	((SQL::Database*)Database)->ExecuteParameterized (R"(INSERT INTO SCHEDULE VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);)",
													  {
														  std::to_string (Inst.ID = RandomIdx ()),//just generate random rather than use sequential
														  std::to_string(MondayStartHour),
														  std::to_string(MondayEndHour),
														  std::to_string(TuesdayStartHour),
														  std::to_string(TuesdayEndHour),
														  std::to_string(WendsdayStartHour),
														  std::to_string(WendsdayEndHour),
														  std::to_string(ThursdayStartHour),
														  std::to_string(ThursdayEndHour),
														  std::to_string(FridayStartHour),
														  std::to_string(FridayEndHour),
														  std::to_string(SaturdayStartHour),
														  std::to_string(SaturdayEndHour),
													  });
	return Inst;
}

void Schedule::Delete ()
{
	((SQL::Database*)Database)->ExecuteParameterized (R"(DELETE FROM SCHEDULE WHERE ID = ?;)",
													  {
														  std::to_string (ID)
													  });
	this->~Schedule ();
}