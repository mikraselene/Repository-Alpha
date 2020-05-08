#ifndef WALLET_H
#define WALLET_H

#include <iostream>

using namespace std;

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
