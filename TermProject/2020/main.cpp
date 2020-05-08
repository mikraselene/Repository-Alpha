#include <iostream>
#include <string>
#include "inc/date.h"
#include "inc/asset.h"
#include "inc/bill.h"
#include "inc/submenu.h"

using namespace std;

template <typename T>
bool func(T A, T B)
{
    return A == B;
}
extern list<Transaction *> pTransaction;

void AssetSubMenu()
{
    double a = 0;
    Date today;
    string c = "hello";
    bool comfirmed = 0;
    while (1)
    {
        printf("金额: ");
        scanf("%lf", &a);
        printf("金额\t\t类别\t\t日期\n");
        printf("%.2lf\t\t%s\t\t", a, c.c_str());
        today.Print();
        printf("确认? (y/n): ");
        getchar();
        char flag;
        scanf("%c", &flag);
        getchar();
        if (flag == 'y')
        {
            break;
        }
    }
    Transaction *temp = new SingleTransaction(a, c, today);
    temp->Add();
}
int main()
{

    TransactionMenu s;
    while (1)
    {
        s.InputAmount();
        cout << endl
             << endl;
    }
    /*
    AssetSubMenu();
    list<Transaction *>::iterator it;
    cout << "金额\t类别\t日期\n";
    for (it = pTransaction.begin(); it != pTransaction.end(); it++)
    {
        (*it)->Print();
    }
    //rg.Add();
    //rg.Del();

    
    DepositAndLoan dp;
    DepositAndLoan dp2;
    dp.Add();
    dp2.Add();
    list<DepositAndLoan *>::iterator it;
    for (it = pDepoAndLoan.begin(); it != pDepoAndLoan.end(); it++)
    {
        (*it)->Print();
    }

    Test("hello");
    Test("i", 7);
    uint year = 2020;
    uint month = 1;
    uint day = 2;
    Year y(2020);
    Month m(1);
    Day x(1);
    Date D(y, m, x);
    Date da;
    D.Print();
    da.Print();

    
    extern list<Bill *> pFiltered;

    Bill b[10];
    Date today;
    for (int i = 0; i < 10; i++)
    {
        Bill *p = new Bill;
        p->Add(10 * i + 100, today, "z");
    }
    FLTR_AMOUNT param = {100, 150};
    Filter f(param);
    f.FilterByAmount();
    list<Bill *>::iterator it;
    for (it = pFiltered.begin(); it != pFiltered.end(); it++)
    {
        (*it)->Print();
    }
    */
}
