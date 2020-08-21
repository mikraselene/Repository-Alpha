#include <iostream>
using namespace std;
int MaxDay(int year, int month)
{
    int maxday[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if ((year % 4 == 0 && year % 400 == 0) || (year % 4 == 0 && year % 100 != 0))
    {
        maxday[2]++;
    }
    return maxday[month];
}

class Date
{
public:
    Date(int year, int month, int day)
    {
        this->year = year;
        this->month = month;
        this->day = day;
    }
    operator int()
    {
        int result = 0;
        for (int i = 1; i < month; i++)
        {
            result += MaxDay(year, i);
        }
        result += day;
        return result;
    }
    Date Add(Date A, int n)
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
        Date date(year, month, day);
        return date;
    }

    int GetYear()
    {
        return year;
    }
    int GetMonth()
    {
        return month;
    }
    int GetDay()
    {
        return day;
    }

private:
    int year;
    int month;
    int day;
};
void Out(Date A)
{
    Date B = A.Add(A, 1039);
    cout << int(A) << endl;
    cout << B.GetYear() << " " << B.GetMonth() << " " << B.GetDay() << endl;
}
int main()
{
    int y, m, d;
    while (cin >> y >> m >> d)
    {
        Date A(y, m, d);
        Out(A);
    }
}