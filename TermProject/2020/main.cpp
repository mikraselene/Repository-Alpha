#include "Asset.h"
#include <iostream>

int main()
{
    list<Transaction *> pTransaction;
    SingleTransaction sg;
    RegularTransaction rg;
    sg.Add();
    rg.Add();
    rg.Del();
    for (int i = 0; i < 3; i++)
    {
        DepositAndLoan dp;
        dp.Add();
    }
    list<DepositAndLoan *>::iterator it;
    for (it = pDepoAndLoan.begin(); it != pDepoAndLoan.end(); it++)
    {
        (*it)->Print();
    }
}
