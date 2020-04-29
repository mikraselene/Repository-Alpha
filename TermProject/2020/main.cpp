#include <iostream>
//#include "src/date.cpp"
#include "inc/date.h"
using namespace std;

int main()
{
    /*
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
*/
    uint year = 2020;
    uint month = 1;
    uint day = 2;
    Year y(2020);
    Month m(1);
    Day d(1);
    Date D(y, m, d);
    Date da;
    D.Print();
    da.Print();
}
