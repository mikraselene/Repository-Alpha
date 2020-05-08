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
Now *pNow = new Now;

#pragma endregion

#pragma region "Year, Month and Day"
Year::Year()
{
    year = pNow->GetCurrentYear();
}
Year::Year(const uint &y)
{
    year = y;
}
uint Year::GetYear() const
{
    return year;
}
Month::Month()
{
    month = pNow->GetCurrentMonth();
}
Month::Month(const uint &m)
{
    month = m;
}
uint Month::GetMonth() const
{
    return month;
}
Day::Day()
{
    day = pNow->GetCurrentDay();
}
Day::Day(const uint &d)
{
    day = d;
}
uint Day::GetDay() const
{
    return day;
}
Year *pYear = new Year;
Month *pMonth = new Month;
Day *pDay = new Day;

#pragma endregion

#pragma region "Date"
Date::Date()
{
    year = *pYear;
    month = *pMonth;
    day = *pDay;
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

bool operator>(Date A, Date B)
{
    int x = A.year.GetYear() * 10000 + A.month.GetMonth() * 100 + A.day.GetDay();
    int y = B.year.GetYear() * 10000 + B.month.GetMonth() * 100 + B.day.GetDay();
    return x > y;
}

bool operator>=(Date A, Date B)
{
    return (A == B || A > B);
}
bool operator==(Date A, Date B)
{
    return (A.year.GetYear() == B.year.GetYear() &&
            A.month.GetMonth() == B.month.GetMonth() &&
            A.day.GetDay() == B.day.GetDay());
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

#pragma endregion
