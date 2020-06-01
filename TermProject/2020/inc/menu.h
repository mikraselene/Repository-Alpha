#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <memory>

#include "date.h"
#include "input.h"
#include "text.h"
#include "period.h"
#include "category.h"
#include "bill.h"
#include "asset.h"
#include "wallet.h"
#include "fitting.h"
#include "refresh.h"

class MainMenu
{
public:
    virtual void Menu() const;

protected:
    virtual void InputCode() const;
    int SetCode() const;
};

class AssetMenu : public MainMenu
{
protected:
    void Menu() const;
    void InputCode() const;
    virtual void PrintAll() const;
};

class TransactionMenu : public AssetMenu
{
public:
    void PrintAll() const;
    enum
    {
        EXPENSE = -1,
        INCOME = 1,
    };

private:
    void Menu() const;
    void InputCode() const;
    void EditTransaction() const;
    void InputEditCode() const;
};
class DepositAndLoanMenu : public AssetMenu
{
private:
    void Menu() const;
    void InputCode() const;
    void PrintAll() const;
    void GetStats() const;
    void EditDepositAndLoan() const;
    void InputEditCode() const;
    enum
    {
        DEPOSIT = 1,
        LOAN = -1,
    };
};

class BillMenu : public MainMenu
{
private:
    void Menu() const;
    void InputCode() const;
};
class OverviewMenu : public BillMenu
{
private:
    void Menu() const;
    void InputCode() const;
    void PrintAll(const int &) const;
};
class FilterMenu : public BillMenu
{
private:
    double SetAmount() const;
    Date SetDate() const;
    int SetType() const;

    void FilterByAmount() const;
    void FilterByDate() const;
    void FilterByType() const;
    void Menu() const;
    void InputCode() const;
    void PrintFiltered() const;

    template <typename T1, typename T2>
    void PrintFilterBody(const T1 &, const T2 &) const;
};
class StatisticsMenu : public BillMenu
{
private:
    void Menu() const;
    void PrintStats() const;
    void Fitting() const;
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
    void Menu() const;
    void InputCode() const;
};

class FileMenu : public MainMenu
{
private:
    void Menu() const;
    void InputCode() const;
};

#endif
