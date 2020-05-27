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
            it->GetPeriod().Calculate(it->GetDate());
            extern std::vector<Date *> dateList;
            for (auto itDate : dateList)
            {
                using namespace NBill;
                Bill *t = new Bill(it->GetType(), it->GetAmount(),
                                   *itDate, it->GetCategory() + " (" + REGULAR + ")");
                t->Add();
            }
            it->ResetDate();
            dateList.clear();
        }
    }
    for (auto it : pDepoAndLoan)
    {
        int code = it->GetPeriod();
        int sum = 0;
        if (code == Period::MONTHLY ||
            code == Period::WEEKLY ||
            code == Period::DAILY)
        {
            it->GetPeriod().Calculate(it->GetDate());
            extern std::vector<Date *> dateList;
            for (auto itDate : dateList)
            {
                using namespace NBill;
                it->Check();
                Bill *t = new Bill(it->GetType(), it->GetRate() * it->GetAmount(),
                                   *itDate, it->GetInfo() + " (" + INTEREST + ")");
                t->Add();
                sum += it->GetRate() * it->GetAmount();
            }
            it->ResetDate();
            dateList.clear();
        }
        it->ChangeTotalInterest(sum);
    }
}