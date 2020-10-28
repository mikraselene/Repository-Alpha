#include <iostream>
using namespace std;
class Date
{
public:
    void SetDate(int y, int m, int d)
    {
        year = y;
        month = m;
        day = d;
    }
    bool IsLeapYear()
    {
        return (!year % 4 && year % 100) || (!year % 400);
    }
    void PrintDate()
    {
        printf("%d.%d.%d\n", year, month, day);
    }

private:
    int year;
    int month;
    int day;
};

int main()
{
    Date test;
    Date *pt;
    pt->SetDate(1145, 1, 4);
    test.SetDate(1919, 8, 10);
    pt->PrintDate();
    test.PrintDate();
}