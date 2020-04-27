#include <iostream>
#include "date/date.cpp"
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
    //Year y;
    //Month m;
    //Day d;
    Date da(Year(1111), Month(1), Day(123));
    Date d;
    d.Print();
    da.Print();
}
