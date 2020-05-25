#ifndef WALLET_H
#define WALLET_H

#include <iostream>
#include "text.h"
#include "input.h"

class Wallet
{
public:
    Wallet(double);

    double SetAmount();

    void TopUp();
    void Withdraw();
    void Edit();

    void Change(double);
    double GetBalance();

private:
    double balance;
};

#endif
