#ifndef ASSET_H
#define ASSET_H

#include <iostream>

#include "date.h"
#include "input.h"
#include "text.h"
#include "period.h"
#include "category.h"
#include "menu.h"
#include "bill.h"

class Asset
{
protected:
    double SetAmount();
    Date SetDate();
    Category SetCategory();
    Period SetPeriod();
    int SetCode();
    void ShowCategory();
    void PrintInstruction();
};

struct TRANSACTION_DATA
{
    int type;
    double amount;
    Category category;
    Date date;
    Date tempDate;
    Period period;
};
class Transaction : public Asset
{
    friend class File;
    friend class Refresh;
    friend class TransactionMenu;

private:
    void InputSingleTransaction(int);
    void InputRegularTransaction(int);
    Period GetPeriod();
    void SetId(int);
    void SingleSubmenu();
    void RegularSubmenu();
    void SetData(TRANSACTION_DATA);
    TRANSACTION_DATA GetData();
    Date GetTempDate();
    void AddToBill(Date *);
    void ResetDate();
    void Print();
    void Edit();

    template <typename T1, typename T2, typename T3>
    void PrintEdit(T1 x, T2 y, T3 z);

    template <typename T1, typename T2, typename T3>
    void PrintSingleBody(T1, T2, T3);

    template <typename T1, typename T2, typename T3, typename T4>
    void PrintRegularBody(T1 x, T2 y, T3 z, T4 u);

    void InputSingleCode();
    void InputRegularCode();

    double amount;
    Category category;
    Date tempDate;
    Date date;
    Period period;
    int type;
    int id;
};

struct DEPOSIT_AND_LOAN_DATA
{
    bool isCompound;
    int type;
    double principle;
    double tempPrinciple;
    double rate;
    double totalInterest;
    Date date;
    Date tempDate;
    Period period;
    string info;
};
class DepositAndLoan : public Asset
{
    friend class File;
    friend class Refresh;
    friend class DepositAndLoanMenu;

private:
    void InputDepositAndLoan(int);

    double GetTotalInterest();
    void PrintTotalInterest();

    void SetId(int);

    void Submenu();

    void SetData(DEPOSIT_AND_LOAN_DATA);
    DEPOSIT_AND_LOAN_DATA GetData();

    Date GetTempDate();
    Period GetPeriod();

    void AddToBill(Date *);
    void CheckCompound();
    void ResetDate();

    void Print();
    void Edit();

    double SetRate();
    bool SetType();
    string SetInfo();

    template <typename T1, typename T2, typename T3,
              typename T4, typename T5, typename T6>
    void PrintDepoLoanBody(T1 x, T2 y, T3 z, T4 u, T5 v, T6 w);
    void InputCode();

    bool isCompound;
    int type;
    double principle;
    double tempPrinciple;
    double rate;
    double totalInterest;
    Date date;
    Date tempDate;
    Period period;
    string info;
    int id;
};

#endif
