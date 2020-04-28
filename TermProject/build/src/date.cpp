#include <iostream>
#include <ctime>

#include "../include/date.h"

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
uint Now::GetCurrentYear() const
{
    return currentYear;
}
uint Now::GetCurrentMonth() const
{
    return currentMonth;
}
uint Now::GetCurrentDay() const
{
    return currentDay;
}

Year::Year(const uint &y)
{
    year = y;
}
uint Year::GetYear() const
{
    return year;
}

Month::Month(const uint &m)
{
    month = m;
}
uint Month::GetMonth() const
{
    return month;
}

Day::Day(const uint &d)
{
    day = d;
}
uint Day::GetDay() const
{
    return day;
}

Date::Date(const Year &y, const Month &m, const Day &d)
{
    year = y;
    month = m;
    day = d;
}
void Date::Print()
{
    printf("%u-", year.GetYear());
    printf("%u-", month.GetMonth());
    printf("%u\n", day.GetDay());
}