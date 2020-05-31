#include "../inc/period.h"

std::vector<Date *> dateList;

Period::Period(const int &code)
{
    this->code = code;
    if (code == MONTHLY)
    {
        period = NPeriod::STR_MONTHLY;
    }
    else if (code == WEEKLY)
    {
        period = NPeriod::STR_WEEKLY;
    }
    else if (code == DAILY)
    {
        period = NPeriod::STR_DAILY;
    }
    else
    {
        period = NPeriod::STR_NO_PERIOD;
    }
}

Period::Period()
{
    this->code = 1;
    period = NPeriod::STR_MONTHLY;
}

std::ostream &operator<<(std::ostream &out, const Period &A)
{
    std::cout << A.period;
    return out;
}

Period::operator int()
{
    return code;
}

/*---------------------------------------------------------------------------
函数: int Calculate()

目的:
    计算出给定起始日期到当前日期的间隔周期数 x.

返回值:
    整数 x.
---------------------------------------------------------------------------*/
int Period::Calculate(const Date &start) const
{
    Date today;
    Date *temp = new Date;
    *temp = start;
    int cnt = 0;
    while (*temp < today)
    {
        Date *pt = new Date;
        *pt = *temp;
        dateList.push_back(pt);
        cnt++;
        if (code == MONTHLY)
        {
            *temp = *temp + MaxDay(temp->GetYear(), temp->GetMonth());
        }
        else if (code == WEEKLY)
        {
            *temp = *temp + 7;
        }
        else if (code == DAILY)
        {
            *temp = *temp + 1;
        }
    }
    return cnt;
}
