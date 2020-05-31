#include "../inc/date.h"

#pragma region "Today"

Now::Now()
{
    time_t rawTime;
    time(&rawTime);
    struct tm *currentTime;
    currentTime = localtime(&rawTime);
    currentYear = currentTime->tm_year + 1900;
    currentMonth = currentTime->tm_mon + 1;
    currentDay = currentTime->tm_mday;
}
const Now *const pNow = new Now;
//TODO:

#pragma endregion

#pragma region "Year, Month and Day"

Year::Year()
{
    this->year = pNow->currentYear;
}

Year::Year(const int &year)
{
    this->year = year;
}

Month::Month()
{
    this->month = pNow->currentMonth;
}

Month::Month(const int &month)
{
    this->month = month;
}

Day::Day()
{
    this->day = pNow->currentDay;
}

Day::Day(const int &day)
{
    this->day = day;
}

#pragma endregion

#pragma region "Date"

Date::Date()
{
    Year year;
    Month month;
    Day day;
    this->year = year;
    this->month = month;
    this->day = day;
}

Date::Date(const Year &year, const Month &month, const Day &day)
{
    this->year = year;
    this->month = month;
    this->day = day;
}

/*---------------------------------------------------------------------------
函数: bool IsLegal()

目的:
    判断给定的日期是否合法.

返回值:
    1, 如果日期格式是合法的;
    0, 如果日期格式是非法的.
---------------------------------------------------------------------------*/
bool Date::IsLegal() const
{
    int year = GetYear();
    int month = GetMonth();
    int day = GetDay();
    return month > 0 && month <= 12 && day > 0 && day <= MaxDay(year, month);
}

/*---------------------------------------------------------------------------
重载: operator int()

目的:
    获取从 0001/01/01 到给定的日期的间隔天数 x.

返回值:
    整数 x.
---------------------------------------------------------------------------*/
Date::operator int() const
{
    int year = GetYear();
    int month = GetMonth();
    int day = GetDay();
    int result = 0;
    for (int i = 1; i < year; i++)
    {
        result += 365;
        if ((i % 4 == 0 && i % 100 != 0) || i % 400 == 0)
        {
            result++;
        }
    }
    for (int i = 1; i < month; i++)
    {
        result += MaxDay(year, i);
    }
    result += day;
    return result;
}

bool operator>(const Date &A, const Date &B)
{
    return int(A) > int(B);
}

bool operator>=(const Date &A, const Date &B)
{
    return (A == B || A > B);
}

bool operator==(const Date &A, const Date &B)
{
    return int(A) == int(B);
}

bool operator<(const Date &A, const Date &B)
{
    return !(A >= B);
}

bool operator<=(const Date &A, const Date &B)
{
    return !(A > B);
}

bool operator!=(const Date &A, const Date &B)
{
    return !(A == B);
}

/*---------------------------------------------------------------------------
函数: int operator-(Date, Date)

目的:
    获取给定两个日期的间隔 x.

返回值:
    整数 x.
---------------------------------------------------------------------------*/
int operator-(const Date &A, const Date &B)
{
    return int(A) - int(B);
}

/*---------------------------------------------------------------------------
函数: Date operator+(Date, int)

目的:
    获取给定日期 A 后 n 天的日期 X.

返回值:
    日期 X.
---------------------------------------------------------------------------*/
Date operator+(const Date &A, const int &n)
{
    int count = 0;
    int year = A.GetYear();
    int month = A.GetMonth();
    int day = A.GetDay();
    for (int i = 1; i < month; ++i)
    {
        count += MaxDay(year, i);
    }
    count += day;
    for (int i = 0; i < n; i++)
    {
        if (day == MaxDay(year, month))
        {
            day = 1;
            if (month == 12)
            {
                year++;
                month = 1;
            }
            else
            {
                month++;
            }
        }
        else
        {
            day++;
        }
    }
    Year Y(year);
    Month M(month);
    Day D(day);
    Date date(Y, M, D);
    return date;
}

std::ostream &operator<<(std::ostream &out, const Date &A)
{
    using namespace NDate;
    std::string datestr = std::to_string(A.GetYear()) + "/" +
                          std::to_string(A.GetMonth()) + "/" +
                          std::to_string(A.GetDay());
    std::cout << datestr;
    return out;
}

int Date::GetYear() const
{
    return year.year;
}

int Date::GetMonth() const
{
    return month.month;
}

int Date::GetDay() const
{
    return day.day;
}

/*---------------------------------------------------------------------------
函数: int MaxDay(const int &, const int &)

目的:
    获得给定月份的最大天数 x.

返回值:
    整数 x.
---------------------------------------------------------------------------*/
int MaxDay(const int &year, const int &month)
{
    int maxday[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if ((year % 4 == 0 && year % 400 == 0) || (year % 4 == 0 && year % 100 != 0))
    {
        maxday[2]++;
    }
    return maxday[month];
}

#pragma endregion
