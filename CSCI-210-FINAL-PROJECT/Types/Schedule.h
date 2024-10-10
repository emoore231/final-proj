#pragma once

#include <string>
#include "../property.h"


class Schedule
{
private:
    void* Database;
    size_t ID;
    Schedule ();

public:
    Schedule (const size_t _ID, void* _Database);

    static Schedule New
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
    );

    void Delete ();

    property (MondayStartHour, Schedule, size_t);
    property (MondayEndHour, Schedule, size_t);
    property (TuesdayStartHour, Schedule, size_t);
    property (TuesdayEndHour, Schedule, size_t);
    property (WendsdayStartHour, Schedule, size_t);
    property (WendsdayEndHour, Schedule, size_t);
    property (ThursdayStartHour, Schedule, size_t);
    property (ThursdayEndHour, Schedule, size_t);
    property (FridayStartHour, Schedule, size_t);
    property (FridayEndHour, Schedule, size_t);
    property (SaturdayStartHour, Schedule, size_t);
    property (SaturdayEndHour, Schedule, size_t);
};
