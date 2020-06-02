//OK
#ifndef BILL_H
#define BILL_H

#include <iostream>
#include <vector>
#include <iomanip>

#include "date.h"
#include "period.h"
#include "wallet.h"

/*---------------------------------------------------------------------------
类名: Bill 

描述:
    账单类, 用于实现对账单的管理操作.
---------------------------------------------------------------------------*/
class Bill : public std::enable_shared_from_this<Bill>
{
public:
    struct DATA
    {
        int type;
        double amount;
        Date date;
        std::string info;
    };
    enum
    {
        INCOME = 1,
        EXPENSE = -1,
    };
    Bill(const int &, const double &, const Date &, const std::string &);

    void Add();
    void Print() const;

    DATA GetData() const;
    int GetType() const;
    double GetAmount() const;
    Date GetDate() const;

private:
    int type;
    double amount;
    Date date;
    std::string info;
};

/*---------------------------------------------------------------------------
类名: Filter 

描述:
    过滤器类, 用于实现对账单的过滤.
---------------------------------------------------------------------------*/
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
