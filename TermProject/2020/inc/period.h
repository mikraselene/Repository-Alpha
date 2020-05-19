#ifndef PERIOD_H
#define PERIOD_H

#include <iostream>

#include "date.h"

using std::string;

/*
const string MONTHLY = "";
const string WEEKLY = "";
const string DAILY = "";
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

        int maxday[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if ((y % 4 == 0 && y % 400 == 0) || (y % 4 == 0 && y % 100 != 0))
        {
            maxday[2]++;
        }

        Date *pt = new Date;
        while (1)
        {
            if (m <= 12)
            {
                pt = new Date(y, m, d);
                if (*pt >= startDate)
                {
                    break;
                }
                if (pt->isLegal() == 0)
                {
                    pt = new Date(y, m, maxday[m]);
                }
                m++;
                dateList.push_back(pt);
                cout << *pt << endl;
            }
            else
            {
                m = 1;
                y++;
            }
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

*/
#endif
