#include <iostream>
#include <list>
#include <string>
#include "Date.h"
#include "Period.h"

using namespace std;

void Test(string test)
{
    cout << "Test: " << test << endl;
}

class Transaction;
class DepositAndLoan;
class Budget;
list<Transaction *> pTransaction;
list<DepositAndLoan *> pDepoAndLoan;
list<Budget *> pBudget;

class IAssetManagement
{
public:
    virtual void Add() = 0;
    virtual void Edit() = 0;
    virtual void Del() = 0;
    virtual void Print() = 0;
};

class Transaction : public IAssetManagement
{
public:
    virtual void Add()
    {
        pTransaction.push_back(this);
    }
    virtual void Edit()
    {
    }
    virtual void Del()
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
    virtual void Print()
    {
        Test("Transaction");
    }

protected:
    string category;
    double amount;
    int typeFlag;
};

class SingleTransaction : public Transaction
{
public:
    SingleTransaction()
    {
    }
    void Add()
    {
        pTransaction.push_back(this);
    }
    void Print()
    {
        Test("Single");
    }

private:
    Date date;
};
class RegularTransaction : public Transaction
{
public:
    void Print()
    {
        Test("Regular");
    }

private:
    Date startDate;
    Period period;
};

class Budget : public IAssetManagement
{
public:
    void WriteIn()
    {
    }
    void Add()
    {
        pBudget.push_back(this);
    }
    void Edit()
    {
        Print();
        WriteIn();
    }
    void Del()
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
    void Print()
    {
    }

private:
    string category;
    double amount;
    Date startDate;
    Period period;
};

class DepositAndLoan : public IAssetManagement
{
public:
    void Add()
    {
        WriteIn();
        pDepoAndLoan.push_back(this);
    }
    void Edit()
    {
        printf("Current Deposit/Loan is:\n");
        Print();
        WriteIn();
    }
    void Del()
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
    void Print()
    {
        printf("Principle: %lf\n", principle);
        printf("Interest: %lf\n", interest);
        printf("Info: %s\n", info.c_str());
        Test("DepositAndLoan");
    }

private:
    void WriteIn()
    {
        printf("Principle: ");
        scanf("%lf", &principle);
        printf("Interest: ");
        scanf("%lf", &interest);
        printf("Info: ");
        getchar();
        getline(cin, info);
    }
    string info;
    double principle;
    Date startDate;
    Date endDate;
    double interest;
    Period interestPeriod;
    int typeFlag;
};
