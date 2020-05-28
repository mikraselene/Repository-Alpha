#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <algorithm>
#include <numeric>
#include <iomanip>

#include "asset.h"
#include "date.h"
#include "input.h"
#include "text.h"
#include "period.h"
#include "category.h"
#include "bill.h"
#include "sub.h"
#include "wallet.h"
#include "fitting.h"
#include "refresh.h"

using std::setfill;
using std::setw;

class MainMenu
{
public:
    virtual void Menu();

protected:
    virtual void InputCode();
    int SetCode();
};

class AssetMenu : public MainMenu
{
protected:
    void Menu();
    void InputCode();
    virtual void PrintAll();
};

class TransactionMenu : public AssetMenu
{
public:
    void PrintAll();
    enum
    {
        EXPENSE = -1,
        INCOME = 1,
    };

private:
    void Menu();
    void InputCode();
    void EditTransaction();
};
class DepositAndLoanMenu : public AssetMenu
{
private:
    void Menu();
    void InputCode();
    void PrintAll();
    void GetStats();
    void EditDepositAndLoan();
    enum
    {
        DEPOSIT = 1,
        LOAN = -1,
    };
};
class BudgetMenu : public AssetMenu
{
private:
    void Menu();
    void InputCode();
    void PrintAll();
    void GetStats();
    void EditBudget();
};

class BillMenu : public MainMenu
{
private:
    void Menu();
    void InputCode();
};
class OverviewMenu : public BillMenu
{
private:
    void Menu();
    void InputCode();
    void PrintAll(int);
};
class FilterMenu : public BillMenu
{
private:
    void Menu();
};
class StatisticsMenu : public BillMenu
{
private:
    void Menu();
    void PrintStats();
    void Fitting();
    struct BILL_BY_MONTH
    {
        int year;
        int month;
        double amount;
    };
};

class WalletMenu : public MainMenu
{
private:
    void Menu();
    void InputCode();
};

class FileMenu : public MainMenu
{
private:
    void Menu();
};

class HelpMenu : public MainMenu
{
private:
    void Menu();
    void Refresh();
};

#endif
