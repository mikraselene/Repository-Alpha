#ifndef SUBMENU_H
#define SUBMENU_H

#include <iostream>

#include "asset.h"
#include "date.h"
#include "input.h"
#include "text.h"
#include "period.h"
#include "category.h"
#include "menu.h"
#include "bill.h"

class Asset
{
public:
    void SubMenu();

protected:
    double SetAmount();
    Date SetDate();
    Category SetCategory();
    Period SetPeriod();
    int SetCode();

    void ShowCategory();
    void PrintInstruction();
};

class Transaction : public Asset
{
public:
    void SubMenu();
    void InputSingleTransaction(int);
    void InputRegularTransaction(int);
    int GetType();
    double GetAmount();
    Date GetDate();
    Period GetPeriod();
    string GetCategory();
    void Print();
    void PrintAll();
    void ResetDate();

private:
    template <typename T1, typename T2, typename T3>
    void PrintSingleBody(T1, T2, T3);
    template <typename T1, typename T2, typename T3, typename T4>
    void PrintRegularBody(T1 x, T2 y, T3 z, T4 u);
    void InputSingleCode();
    void InputRegularCode();
    double amount;
    Category category;
    Date date;
    Period period;
    int type;
};

class DepositAndLoan : public Asset
{
public:
    void SubMenu();

    void InputDepositAndLoan(int);

    int GetType();
    double GetAmount();
    double GetRate();
    Date GetDate();
    Period GetPeriod();
    string GetInfo();

    void Print();
    void PrintAll();

    void Check();
    void ChangeTotalInterest(double);
    void ResetDate();

private:
    double SetRate();
    bool SetType();
    string SetInfo();

    template <typename T1, typename T2, typename T3,
              typename T4, typename T5, typename T6>
    void PrintDepoLoanBody(T1 x, T2 y, T3 z, T4 u, T5 v, T6 w);
    void InputCode();

    bool isCompound;
    double principle;
    double interest;
    double totalInterest;
    Date start;
    Period period;
    string info;
    int type;
};

class Budget : public Asset
{
public:
    void SubMenu();

    void InputBudget();

    void Print();
    void PrintAll();

private:
    template <typename T1, typename T2, typename T3>
    void PrintBudgetBody(T1 x, T2 y, T3 z);
    void InputCode();

    double budget;
    Category category;
    Date start;
};

#endif
