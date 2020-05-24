#include <iostream>
#include <string>
#include "inc/date.h"
#include "inc/asset.h"
#include "inc/bill.h"
#include "inc/menu.h"
#include "inc/category.h"

using namespace std;

int main()
{

    AddDefault();
    extern MainMenu *pMenu;
    pMenu->Menu();

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
}
