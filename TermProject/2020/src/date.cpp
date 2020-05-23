#include "../inc/date.h"

using namespace std;

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

Now *pNow = new Now;

#pragma endregion

#pragma region "Year, Month and Day"
Year::Year()
{
    this->year = pNow->currentYear;
}
Year::Year(const uint &year)
{
    this->year = year;
}

Month::Month()
{
    this->month = pNow->currentMonth;
}
Month::Month(const uint &month)
{
    this->month = month;
}

Day::Day()
{
    this->day = pNow->currentDay;
}
Day::Day(const uint &day)
{
    this->day = day;
}

#pragma endregion

#pragma region "Date"
Date::Date()
{
    Year *pYear = new Year;
    Month *pMonth = new Month;
    Day *pDay = new Day;
    this->year = *pYear;
    this->month = *pMonth;
    this->day = *pDay;
}
Date::Date(const Year &year, const Month &month, const Day &day)
{
    this->year = year;
    this->month = month;
    this->day = day;
}

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
    using namespace NDate;
    cout << A.GetYear() << YEAR
         << A.GetMonth() << MONTH
         << A.GetDay() << DAY;
    return out;
}

#pragma endregion
