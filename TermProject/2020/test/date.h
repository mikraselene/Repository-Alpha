#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <ctime>
#include <stdio.h>

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
    uint m_currentYear;
    uint m_currentMonth;
    uint m_currentDay;
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
    uint m_year;
};
class Month
{
public:
    Month();
    Month(const uint &);
    friend class Date;

protected:
    uint m_month;
};
class Day
{
public:
    Day();
    Day(const uint &);
    friend class Date;

protected:
    uint m_day;
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
    bool IsLegal();
    int GetYear();
    int GetMonth();
    int GetDay();
    friend std::ostream &operator<<(std::ostream &, Date);

private:
    Year m_year;
    Month m_month;
    Day m_day;
};

#pragma endregion

#endif
