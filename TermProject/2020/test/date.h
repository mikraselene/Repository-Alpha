#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <ctime>

#pragma region "Today"
class Now
{
public:
    Now();
    uint GetCurrentYear() const;
    uint GetCurrentMonth() const;
    uint GetCurrentDay() const;

private:
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
    uint GetYear() const;

private:
    uint year;
};
class Month
{
public:
    Month();
    Month(const uint &);
    uint GetMonth() const;

private:
    uint month;
};
class Day
{
public:
    Day();
    Day(const uint &);
    uint GetDay() const;

private:
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
    operator int();
    bool isLegal();
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

#endif
