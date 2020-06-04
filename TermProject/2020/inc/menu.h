#ifndef MENU_H
#define MENU_H

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <memory>
#include <numeric>

#include "asset.h"
#include "bill.h"
#include "category.h"
#include "date.h"
#include "file.h"
#include "fitting.h"
#include "input.h"
#include "period.h"
#include "refresh.h"
#include "text.h"
#include "wallet.h"

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
private:
    enum
    {
        EXPENSE = -1,
        INCOME = 1,
    };
    void Menu() const;
    void InputCode() const;
    void PrintAll() const;
    void EditTransaction() const;
    void InputEditCode() const;
};

class DepositAndLoanMenu : public AssetMenu
{
private:
    enum
    {
        DEPOSIT = 1,
        LOAN = -1,
    };
    void Menu() const;
    void InputCode() const;
    void PrintAll() const;
    void EditDepositAndLoan() const;
    void InputEditCode() const;
    void GetStats() const;
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
    void Menu() const;
    void InputCode() const;
    void PrintFiltered() const;

    double SetAmount() const;
    Date SetDate() const;
    int SetType() const;

    void FilterByAmount() const;
    void FilterByDate() const;
    void FilterByType() const;

    template <typename T1, typename T2>
    void PrintFilterBody(const T1 &, const T2 &) const;
};
class StatisticsMenu : public BillMenu
{
private:
    struct BILL_BY_MONTH
    {
        int year;
        int month;
        double amount;
    };
    void Menu() const;
    void PrintStats() const;
    void Fitting() const;
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
