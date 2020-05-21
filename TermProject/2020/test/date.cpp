#include "date.h"

using namespace std;

#pragma region "Today"

/*---------------------------------------------------------------------------
FUNCTION: <Funtion prototype>
PURPOSE:
 <Function description>
---------------------------------------------------------------------------*/

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

Now now;

#pragma endregion

#pragma region "Year, Month and Day"
Year::Year()
{
    year = now.currentYear;
}
Year::Year(const uint &year)
{
    this->year = year;
}

Month::Month()
{
    month = now.currentMonth;
}
Month::Month(const uint &month)
{
    this->month = month;
}

Day::Day()
{
    day = now.currentDay;
}
Day::Day(const uint &day)
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
    year = year;
    month = month;
    day = day;
}
Date::Date(const Year &y, const Month &m, const Day &d)
{
    year = y;
    month = m;
    day = d;
}

/*---------------------------------------------------------------------------
FUNCTION: IsLegal()

PURPOSE:
    To determine whether the format of the date is legal or not.
    
RETURN VALUE:
    1, if the format of the date is legal;
    0, if the format of the date is illegal.
---------------------------------------------------------------------------*/
bool Date::IsLegal()
{
    int maxday[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int year = GetYear();
    int month = GetMonth();
    int day = GetDay();
    if ((year % 4 == 0 && year % 400 == 0) || (year % 4 == 0 && year % 100 != 0))
    {
        maxday[2]++;
    }
    return month > 0 && month <= 12 && day > 0 && day <= maxday[month];
}

/*---------------------------------------------------------------------------
FUNCTION: operator int()

PURPOSE:
    To get the interval from Jan 1st 0001 to the given date.

PARAMETERS:
    -

RETURN VALUE:
    The interval from Jan 1st 0001 to the given date.
---------------------------------------------------------------------------*/
Date::operator int()
{
    int maxday[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int year = GetYear();
    int month = GetMonth();
    int day = GetDay();
    if ((year % 4 == 0 && year % 400 == 0) || (year % 4 == 0 && year % 100 != 0))
    {
        maxday[2]++;
    }
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
        result += maxday[i];
    }
    result += day;
    return result;
}
bool operator>(Date A, Date B)
{
    return int(A) > int(B);
}
bool operator>=(Date A, Date B)
{
    return (A == B || A > B);
}
bool operator==(Date A, Date B)
{
    return int(A) == int(B);
}
bool operator<(Date A, Date B)
{
    return !(A >= B);
}
bool operator<=(Date A, Date B)
{
    return !(A > B);
}
bool operator!=(Date A, Date B)
{
    return !(A == B);
}
int operator-(Date A, Date B)
{
    return int(A) - int(B);
}
/*
hello
*/
int Date::GetYear()
{
    return year.year;
}
int Date::GetMonth()
{
    return month.month;
}
int Date::GetDay()
{
    return day.day;
}

ostream &operator<<(ostream &out, Date A)
{
    cout << A.GetYear() << " "
         << A.GetMonth() << " "
         << A.GetDay();
    return out;
}

#pragma endregion
