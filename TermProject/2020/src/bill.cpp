#include "../inc/bill.h"

using namespace std;

#pragma region "Bill"

vector<Bill *> pBill;

Bill::Bill(int type, double amount, Date date, string info)
{
    this->type = type;
    this->amount = amount;
    this->date = date;
    this->info = info;
}
void Bill::Add()
{
    pBill.push_back(this);
    extern Wallet *pWallet;
    pWallet->Change(type * amount);
}

BILL_DATA Bill::GetData()
{
    return {type,
            amount,
            date,
            info};
}

void Bill::Print()
{
    using namespace NBill;
    string typestr;
    double tempamount;
    if (type == 1)
    {
        typestr = NBill::INCOME;
        tempamount = amount;
    }
    else if (type == -1)
    {
        typestr = NBill::EXPENSE;
        tempamount = -amount;
    }

    cout << fixed << setprecision(2)
         << setw(10) << showpos << tempamount << "\t"
         << typestr << "\t\t\t"
         << date << "\t\t"
         << info << endl
         << resetiosflags(ios::showpos);
}
string Bill::GetInfo()
{
    return info;
}
double Bill::GetAmount()
{
    return amount;
}
Date Bill::GetDate()
{
    return date;
}
int Bill::GetType()
{
    return type;
}
bool Bill::IsExpense()
{
    return type == -1;
}

#pragma endregion

#pragma region "Filter"

vector<Bill *> pFiltered;

void Filter::FilterByAmount(double lowerLimit, double upperLimit)
{
    for (auto it : pBill)
    {
        double amount = it->GetAmount();
        if (lowerLimit <= amount && upperLimit >= amount)
        {
            pFiltered.push_back(it);
        }
    }
}
void Filter::FilterByDate(Date lowerLimit, Date upperLimit)
{
    for (auto it : pBill)
    {
        Date date = it->GetDate();
        if (lowerLimit <= date && upperLimit >= date)
        {
            pFiltered.push_back(it);
        }
    }
}
void Filter::FilterByType(int type)
{
    for (auto it : pBill)
    {
        int itType = it->GetType();
        if (type == itType)
        {
            pFiltered.push_back(it);
        }
    }
}

Filter::Filter()
{
    pFiltered.clear();
}

#pragma endregion
