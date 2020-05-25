#ifndef BILL_H
#define BILL_H

#include <iostream>
#include <vector>

#include "date.h"
#include "period.h"
#include "wallet.h"

using std::string;

class IBillManagement
{
public:
private:
};

class Bill : public IBillManagement
{
public:
    Bill(int, double, Date, string);
    void Add();
    void Hide();
    void Unhide();
    void Print();
    double GetAmount();
    Date GetDate();

private:
    int type;
    double amount;
    Date date;
    std::string info;
    bool isHiden;
};

struct FLTR_DATE
{
    Date lowerLimit;
    Date upperLimit;
};
struct FLTR_AMOUNT
{
    double lowerLimit;
    double upperLimit;
};

class Filter : public IBillManagement
{
public:
    Filter(FLTR_AMOUNT);
    Filter(FLTR_DATE);
    void FilterByAmount();
    void FilterByDate();

private:
    FLTR_AMOUNT fAmount;
    FLTR_DATE fDate;
};

class Search : public IBillManagement
{
public:
    Search();

private:
    std::string sStr;
};

#endif
