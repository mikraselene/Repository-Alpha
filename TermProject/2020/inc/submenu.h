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
    double InputAmount();
    Date InputDate();
    string InputPeriod();
    void PrintInstruction();
    int InputCode();
};

class TransactionMenu : public AssetSubMenu
{
public:
    void InputSingleTransaction();
    void InputRegularTransaction();

    void PrintAllSingle();
    void PrintAllRegular();

private:
    void ShowCategory();
    void InputCategory();

    template <typename T1, typename T2, typename T3>
    void PrintSingleBody(T1, T2, T3);

    template <typename T1, typename T2, typename T3, typename T4>
    void PrintRegularBody(T1 x, T2 y, T3 z, T4 u);

    double amount;
    string category;
    Date date;
    string period;
    int code;
};

class DepositAndLoanMenu : public AssetSubMenu
{
public:
    void InputDepositAndLoan();

    void PrintAllDepositAndLoan();

private:
    double InputRate();
    string InputInfo();

    template <typename T1, typename T2, typename T3,
              typename T4, typename T5, typename T6>
    void PrintDepoLoanBody(T1 x, T2 y, T3 z, T4 u, T5 v, T6 w);

    double principle;
    double interestRate;
    Date start;
    Date end;
    string period;
    string info;
    int code;
    // int typeFlag;
};

#endif
