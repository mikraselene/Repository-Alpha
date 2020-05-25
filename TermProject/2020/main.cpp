#include <iostream>
#include <string>
#include "inc/date.h"
#include "inc/asset.h"
#include "inc/bill.h"
#include "inc/menu.h"
#include "inc/category.h"

using namespace std;

void Initializer()
{
    //READ FILE
    //DEFAULT_CATEGORY
    //CALCULATE:

    extern vector<Transaction *> pTransaction;
    extern vector<DepositAndLoan *> pDepoAndLoan;
    for (auto it : pTransaction)
    {
        if (it->GetPeriod() == Period::MONTHLY)
        {
        }
        if (it->GetPeriod() == Period::WEEKLY)
        {
        }
        if (it->GetPeriod() == Period::DAILY)
        {
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
    AddDefault();
    /*
    extern MainMenu *pMenu;
    pMenu->Menu();
    */
    Date D(Year(2020), Month(3), Day(25));
    Period K(1);
    K.CalculateWeekly(D);
    extern std::vector<Date *> dateList;
    for (auto it : dateList)
    {
        cout << *it << endl;
    }
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