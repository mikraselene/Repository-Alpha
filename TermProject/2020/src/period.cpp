#include "../inc/period.h"

Period::Period(int code)
{
    using namespace NPeriod;
    this->code = code;
    if (code == MONTHLY)
    {
        period = MONTHLY;
    }
    else if (code == WEEKLY)
    {
        period = WEEKLY;
    }
    else if (code == DAILY)
    {
        period = DAILY;
    }
    else
    {
        period = NO_PERIOD;
    }
}

Period::Period()
{
    using namespace NPeriod;
    this->code = 1;
    period = MONTHLY;
}
std::vector<Date *> dateList;

std::ostream &operator<<(std::ostream &out, Period A)
{
    cout << A.period;
    return out;
}
int Period::CalculateWeekly(Date start)
{
    Date today;
    int y = start.GetYear();
    int m = start.GetMonth();
    int d = start.GetDay();
    Date *temp = new Date;
    *temp = start;
    int cnt = 0;
    while (*temp < today)
    {
        *temp = *temp + 7;
        Date *pt = new Date;
        *pt = *temp;
        dateList.push_back(pt);
        cnt++;
        //cout << *pt << endl;
    }
    return cnt;
}

int Period::CalculateDaily(Date start)
{
    Date today;
    int y = start.GetYear();
    int m = start.GetMonth();
    int d = start.GetDay();
    Date *temp = new Date;
    *temp = start;
    int cnt = 0;
    while (*temp < today)
    {
        *temp = *temp + 1;
        Date *pt = new Date;
        *pt = *temp;
        dateList.push_back(pt);
        cnt++;
        //cout << *pt << endl;
    }
    return cnt;
}

int Period::CalculateMonthly(Date start)
{
    Date today;
    int y = start.GetYear();
    int m = start.GetMonth();
    int d = start.GetDay();
    Date *pt = new Date;
    *pt = start;
    int cnt = 0;
    while (1)
    {
        if (m <= 12)
        {
            pt = new Date(y, m, d);
            if (*pt >= today)
            {
                break;
            }
            if (pt->IsLegal() == 0)
            {
                pt = new Date(y, m, MaxDay(y, m));
            }
            m++;
            dateList.push_back(pt);
            cnt++;
            //cout << *pt << endl;
        }
        else
        {
            m = 1;
            y++;
        }
    }
    return cnt;
}

int Period::GetPeriodCode()
{
    return code;
}