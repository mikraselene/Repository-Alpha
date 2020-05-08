#include <iostream>
#include <list>
#include "date.h"
#include "period.h"

using namespace std;

class IBillManagement
{
public:
private:
};

class Bill : public IBillManagement
{
public:
    Bill(double, Date, string);
    void Add();
    void Hide();
    void Print();
    double GetAmount();
    Date GetDate();

private:
    double amount;
    Date date;
    string info;
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
    string sStr;
};

class Statistics : public IBillManagement
{
};
