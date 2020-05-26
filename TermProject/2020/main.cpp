#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include "inc/date.h"
#include "inc/asset.h"
#include "inc/bill.h"
#include "inc/menu.h"
#include "inc/file.h"
#include "inc/category.h"
#include "inc/fitting.h"

using namespace std;

void Initializer()
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
            }
            it->ResetDate();
            dateList.clear();
        }
    }
}
void Exit()
{
    //SAVE
    //DELETE
}

int main()
{
    extern vector<Bill *> pBill;
    File file;
    file.LoadFromFile();
    extern MainMenu *pMenu;
    pMenu->Menu();
}
#if 0
    DepositAndLoanMenu *pTMenu = new DepositAndLoanMenu;
    for (int i = 0; i < 2; i++)
    {
        pTMenu->InputDepositAndLoan();
    }
    pTMenu->PrintAllDepositAndLoan();

    TransactionMenu *pTMenu = new TransactionMenu;
    for (int i = 0; i < 2; i++)
    {
        pTMenu->InputSingleTransaction();
    }
    pTMenu->PrintAllSingle();
    
    /*
    BudgetMenu *pTMenu = new BudgetMenu;
    for (int i = 0; i < 2; i++)
    {
        pTMenu->InputBudget();
    }
    pTMenu->PrintAllBudget();
    */
#endif