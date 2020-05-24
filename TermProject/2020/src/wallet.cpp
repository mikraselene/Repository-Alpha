#include "../inc/wallet.h"

Wallet *pWallet = new Wallet;

void Wallet::TopUp(double am)
{
    amount += am;
}
void Wallet::Withdraw(double am)
{
    amount -= am;
}
void Wallet::Edit(double am)
{
    amount = am;
}

double Wallet::GetBalance()
{
    return amount;
}