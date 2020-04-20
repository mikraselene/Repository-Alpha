#include <iostream>
#include <list>
#include "Date.h"
using namespace std;

class IBillManagement
{
};
class Bill;
list<Bill *> pBill;

class Bill : public IBillManagement
{
private:
    double amount;
    Date date;
    string info;
};

class Search : public IBillManagement
{
};

class Statistics : public IBillManagement
{
};
