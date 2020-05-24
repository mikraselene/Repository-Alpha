#include "../inc/period.h"

Period::Period(int code)
{
    using namespace NPeriod;
    this->code = code;
    if (code == monthly)
    {
        period = MONTHLY;
    }
    else if (code == weekly)
    {
        period = WEEKLY;
    }
    else if (code == daily)
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
int Period::CalculateWeekly()
{
    Date today;
    int p = (today - start) / 7;
    return amount * p;
}
int Period::CalculateDaily()
{
    Date today;
    int p = today - start;
    return amount * p;
}
int Period::CalculateMonthly()
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
            if (*pt >= start)
            {
                break;
            }
            if (pt->IsLegal() == 0)
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