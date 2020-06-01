//OK
#include "../inc/refresh.h"

/*---------------------------------------------------------------------------
函数: Refresh()

目的:
    根据定期交易和存贷款刷新账单.
---------------------------------------------------------------------------*/
Refresh::Refresh()
{
    extern std::vector<std::shared_ptr<Bill>> pBill;
    extern std::vector<std::shared_ptr<Transaction>> pTransaction;
    extern std::vector<std::shared_ptr<DepositAndLoan>> pDepoAndLoan;
    for (auto it : pTransaction)
    {
        int code = it->GetPeriod();
        if (code != Period::NO_PERIOD)
        {
            it->GetPeriod().Calculate(it->GetTempDate());
            extern std::vector<std::shared_ptr<Date>> dateList;
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
        if (code != Period::NO_PERIOD)
        {
            it->GetPeriod().Calculate(it->GetTempDate());
            extern std::vector<std::shared_ptr<Date>> dateList;
            for (auto itDate : dateList)
            {
                it->AddToBill(itDate);
            }
            it->ResetDate();
            dateList.clear();
        }
    }
}
