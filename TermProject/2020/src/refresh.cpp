#include "../inc/refresh.h"

/*---------------------------------------------------------------------------
函数: Refresh()

目的:
    根据定期交易和存贷款刷新账单.
    
调用:
    GetPeriod();
    Calculate();
    GetTempDate();
    AddToBill();
    ResetDate();
---------------------------------------------------------------------------*/
Refresh::Refresh()
{
    extern std::vector<Transaction *> pTransaction;
    extern std::vector<DepositAndLoan *> pDepoAndLoan;
    extern std::vector<Bill *> pBill;
    for (auto it : pTransaction)
    {
        int code = it->GetPeriod();
        if (code != Period::NO_PERIOD)
        {
            it->GetPeriod().Calculate(it->GetTempDate());
            extern std::vector<Date *> dateList;
            for (auto itDate : dateList)
            {
                it->AddToBill(itDate);
            }
            it->ResetDate();
            DELETE_VECTOR(dateList);
        }
    }
    for (auto it : pDepoAndLoan)
    {
        int code = it->GetPeriod();
        if (code != Period::NO_PERIOD)
        {
            it->GetPeriod().Calculate(it->GetTempDate());
            extern std::vector<Date *> dateList;
            for (auto itDate : dateList)
            {
                it->AddToBill(itDate);
            }
            it->ResetDate();
            DELETE_VECTOR(dateList);
        }
    }
}
