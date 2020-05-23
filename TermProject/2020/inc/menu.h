#ifndef MENU_H
#define MENU_H

#include <iostream>
#include "asset.h"
#include "date.h"
#include "input.h"
#include "text.h"
#include "period.h"
#include "category.h"
#include "sub.h"

class MainMenu
{
public:
    virtual void Menu();

protected:
    int SetCode();
};

class AssetMenu : public MainMenu
{
protected:
    void Menu();
    virtual void PrintAll();
};

class TransactionMenu : public AssetMenu
{
private:
    void Menu();
    void PrintAll();
    void EditTransaction();
    enum
    {
        EXPENSE = -1,
        INCOME = 1,
    };
};
class DepositAndLoanMenu : public AssetMenu
{
private:
    void Menu();
    void PrintAll();
    void GetStats();
    void EditDepositAndLoan();
};
class BudgetMenu : public AssetMenu
{
private:
    void Menu();
    void PrintAll();
    void GetStats();
    void EditBudget();
};

class BillMenu : public MainMenu
{
private:
    void Menu();
};
class OverviewMenu : public BillMenu
{
private:
    void Menu();
};
class FilterMenu : public BillMenu
{
private:
    void Menu();
};
class Statistics : public BillMenu
{
private:
    void Menu();
};

class WalletMenu : public MainMenu
{
private:
    void Menu();
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
};

#endif
