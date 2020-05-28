#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <ctime>
#include <iomanip>

#include "text.h"

#define uint unsigned int

#pragma region "Today"
class Now
{
public:
    Now();
    friend class Year;
    friend class Month;
    friend class Day;

protected:
    uint currentYear;
    uint currentMonth;
    uint currentDay;
};

#pragma endregion

#pragma region "Year, Month and Day"
class Year
{
public:
    Year();
    Year(const uint &);
    friend class Date;

protected:
    uint year;
};
class Month
{
public:
    Month();
    Month(const uint &);
    friend class Date;

protected:
    uint month;
};
class Day
{
public:
    Day();
    Day(const uint &);
    friend class Date;

protected:
    uint day;
};

#pragma endregion

#pragma region "Date"
class Date
{
public:
    Date();
    Date(const Year &, const Month &, const Day &);
    friend bool operator>(Date, Date);
    friend bool operator>=(Date, Date);
    friend bool operator==(Date, Date);
    friend bool operator<(Date, Date);
    friend bool operator<=(Date, Date);
    friend bool operator!=(Date, Date);
    friend int operator-(Date, Date);
    friend Date operator+(Date, int);
    operator int();
    bool IsLegal();
    int GetYear();
    int GetMonth();
    int GetDay();
    friend std::ostream &operator<<(std::ostream &, Date);

private:
    Year year;
    Month month;
    Day day;
};

#pragma endregion

int MaxDay(int, int);

#endif
