//OK
#include "../inc/wallet.h"

std::shared_ptr<Wallet> pWallet = std::make_shared<Wallet>(0);

Wallet::Wallet(const double &balance)
{
    this->balance = balance;
}

/*---------------------------------------------------------------------------
函数: double SetAmount()

目的:
    输入金额 x.

返回值:
    实数 x.
---------------------------------------------------------------------------*/
double Wallet::SetAmount() const
{
    try
    {
        In amount;
        std::cin >> amount;
        return amount;
    }
    catch (const std::string msg)
    {
        std::cerr << msg << ", "
                  << NError::PLEASE_INPUT_AGAIN << ". "
                  << std::endl;
        return SetAmount();
    }
}

void Wallet::TopUp()
{
    std::cout << NWallet::TOP_UP << ": ";
    double amount = SetAmount();
    Date today;
    std::shared_ptr<Bill>
        p = std::make_shared<Bill>(Bill::INCOME, amount, today, NWallet::TOP_UP);
    p->Add();
}

void Wallet::Withdraw()
{
    std::cout << NWallet::WITHDRAW << ": ";
    double amount = SetAmount();
    Date today;
    std::shared_ptr<Bill>
        p = std::make_shared<Bill>(Bill::EXPENSE, amount, today, NWallet::WITHDRAW);
    p->Add();
}

void Wallet::Edit()
{
    std::cout << NWallet::EDIT << ": " << balance << " -> ";
    double amount = SetAmount();
    double delta = amount - balance;
    balance = amount;
    Date today;
    std::shared_ptr<Bill>
        p = std::make_shared<Bill>(delta > 0 ? 1 : -1, delta, today, NWallet::EDIT);
    p->Add();
}

void Wallet::Change(const double &increment)
{
    balance += increment;
}

double Wallet::GetBalance() const
{
    return balance;
}
