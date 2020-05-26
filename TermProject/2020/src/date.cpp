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
    int year = GetYear();
    int month = GetMonth();
    int day = GetDay();
    return month > 0 && month <= 12 && day > 0 && day <= MaxDay(year, month);
}
Date::operator int()
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
Date operator+(Date A, int n)
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

    for (; n > 0; n--)
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

int MaxDay(int year, int month)
{
    int maxday[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if ((year % 4 == 0 && year % 400 == 0) || (year % 4 == 0 && year % 100 != 0))
    {
        maxday[2]++;
    }
    return maxday[month];
}

#pragma endregion
