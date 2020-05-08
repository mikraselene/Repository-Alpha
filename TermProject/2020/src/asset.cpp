#include "../inc/asset.h"

#pragma region "Transaction"

list<Transaction *> pTransaction;

Transaction::Transaction(double a, string s)
{
    amount = a;
    category = s;
}
SingleTransaction::SingleTransaction(double a, string s, Date d)
    : Transaction(a, s)
{
    date = d;
}
RegularTransaction::RegularTransaction(double a, string s, Date d, Period p)
    : Transaction(a, s)
{
    startDate = d;
    period = p;
}

void Transaction::Add()
{
    pTransaction.push_back(this);
}
void Transaction::Edit()
{
}
void Transaction::Del()
{
    list<Transaction *>::iterator it;
    for (it = pTransaction.begin(); it != pTransaction.end(); it++)
    {
        if (*it == this)
        {
            pTransaction.erase(it);
            break;
        }
    }
}
void Transaction::Print()
{
}
void SingleTransaction::WriteIn()
{
}
void SingleTransaction::Print()
{
    std::cout << amount << "\t" << category << "\t";
    date.Print();
    Test("Single");
}

void RegularTransaction::WriteIn()
{
}
void RegularTransaction::Print()
{
    Test("Single");
}

#pragma endregion

#pragma region "Budget"

list<Budget *> pBudget;

void Budget::WriteIn()
{
}
void Budget::Add()
{
    pBudget.push_back(this);
}
void Budget::Edit()
{
    Print();
    WriteIn();
}
void Budget::Del()
{
    list<Budget *>::iterator it;
    for (it = pBudget.begin(); it != pBudget.end(); it++)
    {
        if (*it == this)
        {
            pBudget.erase(it);
            break;
        }
    }
}
void Budget::Print()
{
}

#pragma endregion

#pragma region "Deposit and Loan"

list<DepositAndLoan *> pDepoAndLoan;

void DepositAndLoan::Add()
{
    WriteIn();
    pDepoAndLoan.push_back(this);
}
void DepositAndLoan::Edit()
{
    printf("Current Deposit/Loan is:\n");
    Print();
    WriteIn();
}
void DepositAndLoan::Del()
{
    list<DepositAndLoan *>::iterator it;
    for (it = pDepoAndLoan.begin(); it != pDepoAndLoan.end(); it++)
    {
        if (*it == this)
        {
            pDepoAndLoan.erase(it);
            break;
        }
    }
}
void DepositAndLoan::Print()
{
    printf("Principle: %.2lf\n", principle);
    printf("Interest: %.2lf%%\n", interest * 100);
    printf("Info: %s\n", info.c_str());
}

void DepositAndLoan::WriteIn()
{
    printf("Principle: ");
    scanf("%lf", &principle);
    printf("Interest: ");
    scanf("%lf", &interest);
    printf("Info: ");
    getchar();
    getline(cin, info);
}

#pragma endregion