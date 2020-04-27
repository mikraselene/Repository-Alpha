#ifndef DATE_H
#define DATE_H

#include <iostream>

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
} *pNow = new Now;

class Year
{
public:
    Year(const uint &y = pNow->GetCurrentYear());
    uint GetYear() const;

private:
    uint year;
} *pYear = new Year;

class Month
{
public:
    Month(const uint &m = pNow->GetCurrentMonth());
    uint GetMonth() const;

private:
    uint month;
} *pMonth = new Month;
class Day
{
public:
    Day(const uint &d = pNow->GetCurrentDay());
    uint GetDay() const;

private:
    uint day;
} *pDay = new Day;

class Date
{
public:
    Date(const Year &y = *pYear, const Month &m = *pMonth, const Day &d = *pDay);
    void Print();

private:
    Year year;
    Month month;
    Day day;
};

#endif