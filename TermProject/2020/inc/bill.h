#ifndef BILL_H
#define BILL_H

#include <iostream>
#include <vector>
#include <iomanip>

#include "date.h"
#include "period.h"
#include "wallet.h"

using std::string;

struct BILL_DATA
{
    int type;
    double amount;
    Date date;
    std::string info;
};

class Bill
{
public:
    Bill(int, double, Date, string);
    void Add();
    void Print();
    BILL_DATA GetData();
    bool IsExpense();
    double GetAmount();
    Date GetDate();
    int GetType();
    string GetInfo();
    enum
    {
        INCOME = 1,
        EXPENSE = -1,
    };

private:
    int type;
    double amount;
    Date date;
    std::string info;
};

class Filter
{
    friend class FilterMenu;

private:
    Filter();
    void FilterByAmount(double, double);
    void FilterByDate(Date, Date);
    void FilterByType(int);

private:
};

#endif
