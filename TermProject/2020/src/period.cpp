//OK
#include "../inc/period.h"

std::vector<std::shared_ptr<Date>> dateList;

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
    std::shared_ptr<Date> temp = std::make_shared<Date>();
    *temp = start;
    int cnt = 0;
    while (*temp < today)
    {
        std::shared_ptr<Date> pDate = std::make_shared<Date>();
        *pDate = *temp;
        dateList.push_back(pDate);
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
