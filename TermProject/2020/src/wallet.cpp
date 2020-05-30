#include "../inc/wallet.h"

//TODO:
Wallet *pWallet = new Wallet(0);

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
    Change(amount);
}

void Wallet::Withdraw()
{
    std::cout << NWallet::WITHDRAW << ": ";
    double amount = SetAmount();
    Change(-amount);
}

void Wallet::Edit()
{
    std::cout << NWallet::EDIT << ": " << balance << " -> ";
    double amount = SetAmount();
    balance = amount;
}

void Wallet::Change(const double &increment)
{
    balance += increment;
}

double Wallet::GetBalance() const
{
    return balance;
}
