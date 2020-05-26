#include "../inc/period.h"

Period::Period(int code)
{
    using namespace NPeriod;
    this->code = code;
    if (code == MONTHLY)
    {
        period = STR_MONTHLY;
    }
    else if (code == WEEKLY)
    {
        period = STR_WEEKLY;
    }
    else if (code == DAILY)
    {
        period = STR_DAILY;
    }
    else
    {
        period = STR_NO_PERIOD;
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

int Period::Calculate(Date start)
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
        Date *pt = new Date;
        *pt = *temp;
        dateList.push_back(pt);
        cnt++;
        //cout << *pt << endl;
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

Period::operator int()
{
    return code;
}