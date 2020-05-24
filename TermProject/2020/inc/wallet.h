#ifndef WALLET_H
#define WALLET_H

#include <iostream>

class Wallet
{
public:
    void TopUp(double);
    void Withdraw(double);
    void Edit(double);
    double GetBalance();

private:
    double amount;
};

#endif
