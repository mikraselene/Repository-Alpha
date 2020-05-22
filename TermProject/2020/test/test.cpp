#include <iostream>
#include <vector>
#include <string>

#include "date.h"

using namespace std;

const string MONTHLY = "";
const string WEEKLY = "";
const string DAILY = "";

vector<Date *> dateList;
class Period
{
public:
    Period(int am, int code, Date s)
    {
        amount = am;
        periodCode = code;
        startDate = s;
        if (code == 1)
        {
            period = MONTHLY;
        }
        if (code == 2)
        {
            period = WEEKLY;
        }
        if (code == 3)
        {
            period = DAILY;
        }
    }
    ~Period()
    {
        cout << "hello" << endl;
    }
    int CalculateWeekly()
    {
        Date today;
        int p = (today - startDate) / 7;
        return amount * p;
    }
    int CalculateDaily()
    {
        Date today;
        int p = today - startDate;
        return amount * p;
    }
    int CalculateMonthly()
    {
        Date today;
        int y = today.GetYear();
        int m = today.GetMonth();
        int d = today.GetDay();
        d = 31;
        Date *pt = new Date;
        while (1)
        {
            int maxday[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
            if ((y % 4 == 0 && y % 400 == 0) || (y % 4 == 0 && y % 100 != 0))
            {
                maxday[2]++;
            }
            pt = new Date(y, m % 12 + 1, d);
            if (*pt >= startDate)
            {
                break;
            }
            if (pt->IsLegal() == 0)
            {
                pt = new Date(y, m % 12 + 1, maxday[m % 12 + 1]);
            }
            dateList.push_back(pt);
            m++;
            if (m % 12 == 0)
            {
                y++;
            }
            //delete pt;
        }
        return amount * dateList.size();
    }

private:
    int periodCode;
    string period;
    int per;
    int amount;
    Date startDate;
};

int main()
{
    Date today;

    cout << today;

    Year Y(2022);
    Month M(6);
    Day D(16);
    Date S(Y, M, D);
    Period K(2000, 3, S);
    cout << K.CalculateMonthly() << endl;

    for (auto it : dateList)
    {
        cout << it << endl;
        delete it;
    }
    cout << endl;
    delete &K;
    for (auto it : dateList)
    {
        cout << it << endl;
    }
}
