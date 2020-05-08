#include "../inc/bill.h"

#pragma region "Bill"

list<Bill *> pBill;

Bill::Bill(double a, Date d, string i)
{
    amount = a;
    date = d;
    info = i;
    isHiden = 0;
}
void Bill::Add()
{
    pBill.push_back(this);
}
void Bill::Hide()
{
    isHiden = 1;
}
void Bill::Print()
{
    std::cout << amount << endl;
}
double Bill::GetAmount()
{
    return amount;
}
Date Bill::GetDate()
{
    return date;
}

#pragma endregion

#pragma region "Filter"

list<Bill *> pFiltered;

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
    list<Bill *>::iterator it;
    for (it = pBill.begin(); it != pBill.end(); it++)
    {
        double amount = (*it)->GetAmount();
        if (fAmount.lowerLimit <= amount && fAmount.upperLimit >= amount)
        {
            pFiltered.push_back(*it);
        }
    }
}
void Filter::FilterByDate()
{
    list<Bill *>::iterator it;
    for (it = pBill.begin(); it != pBill.end(); it++)
    {
        Date date = (*it)->GetDate();
        if (fDate.lowerLimit <= date && fDate.upperLimit >= date)
        {
            pFiltered.push_back(*it);
        }
    }
}

#pragma endregion