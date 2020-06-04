#ifndef WALLET_H
#define WALLET_H

#include <iostream>
#include <memory>

#include "input.h"
#include "text.h"

/*---------------------------------------------------------------------------
类名: Wallet

描述:
    钱包类, 实现对钱包的数据操作. 
---------------------------------------------------------------------------*/
class Wallet
{
public:
    Wallet(const double &);

    double SetAmount() const;

    void TopUp();
    void Withdraw();
    void Edit();
    void Change(const double &);

    double GetBalance() const;

private:
    double balance;
};

#endif
