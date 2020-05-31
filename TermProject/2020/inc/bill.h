#ifndef BILL_H
#define BILL_H

#include <iostream>
#include <vector>
#include <iomanip>

#include "date.h"
#include "period.h"
#include "wallet.h"

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
    Bill(const int &, const double &, const Date &, const std::string &);

    void Add();
    void Print() const;

    BILL_DATA GetData() const;

    double GetAmount() const;
    Date GetDate() const;
    int GetType() const;

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
    void FilterByAmount(const double &, const double &) const;
    void FilterByDate(const Date &, const Date &) const;
    void FilterByType(const int &) const;
};

#endif
