#ifndef SUBMENU_H
#define SUBMENU_H

#include <iostream>
#include "../inc/asset.h"
#include "../inc/date.h"
#include "../inc/input.h"
#include "../inc/text.h"
#include "../inc/category.h"

class AssetSubMenu
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

    int code;
};

class TransactionMenu : public AssetSubMenu
{
public:
    void SubMenu();
    void InputSingleTransaction();
    void InputRegularTransaction();

    void PrintAllSingle();
    void PrintAllRegular();

private:
    template <typename T1, typename T2, typename T3>
    void PrintSingleBody(T1, T2, T3);
    template <typename T1, typename T2, typename T3, typename T4>
    void PrintRegularBody(T1 x, T2 y, T3 z, T4 u);

    double amount;
    Category category;
    Date date;
    Period period;
    int type;
};

class DepositAndLoanMenu : public AssetSubMenu
{
public:
    void SubMenu();

    void InputDepositAndLoan();

    void PrintAllDepositAndLoan();

private:
    double SetRate();
    string SetInfo();

    template <typename T1, typename T2, typename T3,
              typename T4, typename T5, typename T6>
    void PrintDepoLoanBody(T1 x, T2 y, T3 z, T4 u, T5 v, T6 w);

    double principle;
    double interest;
    Date start;
    Date end;
    Period period;
    string info;
    // int typeFlag;
};

class BudgetMenu : public AssetSubMenu
{
public:
    void SubMenu();

    void InputBudget();

    void PrintAllBudget();

private:
    template <typename T1, typename T2, typename T3>
    void PrintBudgetBody(T1 x, T2 y, T3 z);

    double budget;
    Category category;
    Date start;
};

#endif
