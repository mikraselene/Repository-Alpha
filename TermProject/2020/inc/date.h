//OK
#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <ctime>
#include <memory>

#include "text.h"

#pragma region "Today"

/*---------------------------------------------------------------------------
类名: Now

描述:
    用于获取现在的日期.
---------------------------------------------------------------------------*/
class Now
{
public:
    Now();
    friend class Year;
    friend class Month;
    friend class Day;

protected:
    int currentYear;
    int currentMonth;
    int currentDay;
};

#pragma endregion

#pragma region "Year, Month and Day"

class Year
{
public:
    Year();
    Year(const int &);
    friend class Date;

protected:
    int year;
};

class Month
{
public:
    Month();
    Month(const int &);
    friend class Date;

protected:
    int month;
};

class Day
{
public:
    Day();
    Day(const int &);
    friend class Date;

protected:
    int day;
};

#pragma endregion

#pragma region "Date"

/*---------------------------------------------------------------------------
类名: Date

描述:
    自定义 Date 数据类型, 实现对 Date 基本的比较运算, 判断是否合法, 输出等功能. 
---------------------------------------------------------------------------*/
class Date
{
public:
    Date();
    Date(const Year &, const Month &, const Day &);
    bool IsLegal() const;
    friend bool operator>(const Date &, const Date &);
    friend bool operator>=(const Date &, const Date &);
    friend bool operator==(const Date &, const Date &);
    friend bool operator<(const Date &, const Date &);
    friend bool operator<=(const Date &, const Date &);
    friend bool operator!=(const Date &, const Date &);
    friend int operator-(const Date &, const Date &);
    friend Date operator+(const Date &, const int &);
    operator int() const;
    int GetYear() const;
    int GetMonth() const;
    int GetDay() const;
    friend std::ostream &operator<<(std::ostream &, const Date &);

private:
    Year year;
    Month month;
    Day day;
};

int MaxDay(const int &, const int &);

#pragma endregion

#endif
