#include "../inc/bill.h"

#pragma region "Bill"

std::vector<std::shared_ptr<Bill>> pBill;

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

/*---------------------------------------------------------------------------
函数: void Add()

目的:
    把一笔账单添加到 pBill 中并改变钱包余额.
---------------------------------------------------------------------------*/
void Bill::Add()
{
    pBill.push_back(shared_from_this());
    extern std::shared_ptr<Wallet> pWallet;
    pWallet->Change(type * amount);
}

/*---------------------------------------------------------------------------
函数: void Print()

目的:
    打印一笔账单之详情, 其中账单数值是带符号实数.
---------------------------------------------------------------------------*/
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

/*---------------------------------------------------------------------------
函数: DATA GetData()

目的:
    获取一笔账单的各个数据, 用于文件写入.

返回值:
    一笔账单的各个数据组成的结构体. 
---------------------------------------------------------------------------*/
Bill::DATA Bill::GetData() const
{
    return {type,
            amount,
            date,
            info};
}

int Bill::GetType() const
{
    return type;
}

double Bill::GetAmount() const
{
    return amount;
}

Date Bill::GetDate() const
{
    return date;
}

#pragma endregion

#pragma region "Filter"

std::vector<std::shared_ptr<Bill>> pFiltered;

Filter::Filter()
{
    pFiltered.clear();
}

/*---------------------------------------------------------------------------
函数: void FilterByAmount(const double &, const double &)

目的:
    根据输入的金额上下限过滤账单, 把通过过滤的单笔账单添加到 pFiltered.
---------------------------------------------------------------------------*/
void Filter::FilterByAmount(const double &lowerLimit, const double &upperLimit) const
{
    pFiltered.clear();
    for (auto it : pBill)
    {
        double amount = it->GetAmount();
        if (lowerLimit <= amount && upperLimit >= amount)
        {
            pFiltered.push_back(it);
        }
    }
}

/*---------------------------------------------------------------------------
函数: void FilterByDate(const Date &, const Date &)

目的:
    根据输入的日期上下限过滤账单, 把通过过滤的单笔账单添加到 pFiltered.
---------------------------------------------------------------------------*/
void Filter::FilterByDate(const Date &lowerLimit, const Date &upperLimit) const
{
    pFiltered.clear();
    for (auto it : pBill)
    {
        Date date = it->GetDate();
        if (lowerLimit <= date && upperLimit >= date)
        {
            pFiltered.push_back(it);
        }
    }
}

/*---------------------------------------------------------------------------
函数: void FilterByType(const int &)

目的:
    根据输入的种类过滤账单, 把通过过滤的单笔账单添加到 pFiltered.
---------------------------------------------------------------------------*/
void Filter::FilterByType(const int &type) const
{
    pFiltered.clear();
    for (auto it : pBill)
    {
        int itType = it->GetType();
        if (type == itType)
        {
            pFiltered.push_back(it);
        }
    }
}

#pragma endregion
