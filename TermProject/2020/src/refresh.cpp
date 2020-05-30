#include "../inc/refresh.h"

Refresh::Refresh()
{
    //READ FILE
    //DEFAULT_CATEGORY
    //CALCULATE:

    extern vector<Transaction *> pTransaction;
    extern vector<DepositAndLoan *> pDepoAndLoan;
    extern vector<Bill *> pBill;
    for (auto it : pTransaction)
    {
        int code = it->GetPeriod();
        if (code == Period::MONTHLY ||
            code == Period::WEEKLY ||
            code == Period::DAILY)
        {
            it->GetPeriod().Calculate(it->GetTempDate());
            extern std::vector<Date *> dateList;
            for (auto itDate : dateList)
            {
                it->AddToBill(itDate);
            }
            it->ResetDate();
            dateList.clear();
        }
    }
    for (auto it : pDepoAndLoan)
    {
        int code = it->GetPeriod();
        if (code == Period::MONTHLY ||
            code == Period::WEEKLY ||
            code == Period::DAILY)
        {
            it->GetPeriod().Calculate(it->GetTempDate());
            extern std::vector<Date *> dateList;
            for (auto itDate : dateList)
            {
                it->AddToBill(itDate);
            }
            it->ResetDate();
            dateList.clear();
        }
    }
}