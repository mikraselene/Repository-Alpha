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
#include "wallet.h"

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

private:
    void Menu();
    void InputCode();
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
    void InputCode();
    void PrintAll();
    void GetStats();
    void EditDepositAndLoan();
    enum
    {
        DEPOSIT = -1,
        LOAN = 1,
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
    void PrintAll();
    void InputCode();
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
};

#endif
