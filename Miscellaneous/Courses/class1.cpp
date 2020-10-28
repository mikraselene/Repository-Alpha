#include <iostream>
using namespace std;
class Time
{
    friend class Date;
    Time(int h = 11, int m = 45, int s = 14)
    {
        hour = h;
        minute = m;
        second = s;
    }

private:
    int hour;
    int minute;
    int second;
};
class Date
{
public:
    Date(int y = 1145, int m = 1, int d = 4)
    {
        year = y;
        month = m;
        day = d;
    }
    Date operator=(const Date &d)
    {
        if (this != &d)
        {
            year = d.year;
            month = d.month;
            day = d.day;
        }
        return *this;
    }
    void Display() const
    {
        cout << year << "-" << month << "-" << day << " ";
        cout << T.hour << ":" << T.minute << ":" << T.second << endl;
    }

private:
    int year;
    int month;
    int day;
    Time T;
};

int main()
{
    Date d1(1919, 8, 10);
    d1.Display();
    Date d2;
    d2 = d1;
    d2.Display();
}