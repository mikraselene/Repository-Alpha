#ifndef WALLET_H
#define WALLET_H

#include <iostream>

class Wallet
{
public:
    void TopUp(double);
    void Withdraw(double);
    void Edit(double);

private:
    double amount;
};

#endif
