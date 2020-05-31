#include "../inc/bill.h"

#pragma region "Bill"

std::vector<Bill *> pBill;

Bill::Bill(const int &type,
           const double &amount,
           const Date &date,
           const std::string &info)
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

void Bill::Print() const
{
    std::string typestr;
    double tempamount;
    if (type == INCOME)
    {
        typestr = NBill::INCOME;
        tempamount = amount;
    }
    else if (type == EXPENSE)
    {
        typestr = NBill::EXPENSE;
        tempamount = -amount;
    }
    std::cout << std::fixed << std::setprecision(2)
              << std::setw(10) << std::showpos << tempamount << "\t"
              << typestr << "\t\t\t"
              << date << "\t\t"
              << info << std::endl
              << std::resetiosflags(std::ios::showpos);
}

BILL_DATA Bill::GetData() const
{
    return {type,
            amount,
            date,
            info};
}

double Bill::GetAmount() const
{
    return amount;
}

Date Bill::GetDate() const
{
    return date;
}

int Bill::GetType() const
{
    return type;
}

#pragma endregion

#pragma region "Filter"

std::vector<Bill *> pFiltered;

void Filter::FilterByAmount(const double &lowerLimit, const double &upperLimit) const
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
void Filter::FilterByDate(const Date &lowerLimit, const Date &upperLimit) const
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
void Filter::FilterByType(const int &type) const
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
    CLEAR_VECTOR(pFiltered);
}

#pragma endregion
