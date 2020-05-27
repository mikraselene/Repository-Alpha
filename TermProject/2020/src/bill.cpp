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
    this->isHiden = 0;
}
void Bill::Add()
{
    pBill.push_back(this);
    extern Wallet *pWallet;
    pWallet->Change(type * amount);
}

void Bill::Hide()
{
    isHiden = 1;
}
void Bill::Unhide()
{
    isHiden = 0;
}

void Bill::Print()
{
    cout << type << "\t";
    cout << fixed << setprecision(2)
         << amount << "\t\t"
         << date << "\t\t"
         << info << "\t\t"
         << endl;
}
double Bill::GetAmount()
{
    return amount;
}
Date Bill::GetDate()
{
    return date;
}
bool Bill::IsExpense()
{
    return type == -1;
}

#pragma endregion

#pragma region "Filter"

vector<Bill *> pFiltered;

Filter::Filter(FLTR_AMOUNT fltr)
{
    fAmount = fltr;
}
Filter::Filter(FLTR_DATE fltr)
{
    fDate = fltr;
}
void Filter::FilterByAmount()
{
    for (auto it : pBill)
    {
        double amount = it->GetAmount();
        if (fAmount.lowerLimit <= amount && fAmount.upperLimit >= amount)
        {
            pFiltered.push_back(it);
        }
    }
}
void Filter::FilterByDate()
{
    for (auto it : pBill)
    {
        Date date = it->GetDate();
        if (fDate.lowerLimit <= date && fDate.upperLimit >= date)
        {
            pFiltered.push_back(it);
        }
    }
}

#pragma endregion
