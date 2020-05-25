#include "../inc/wallet.h"

Wallet *pWallet = new Wallet(0);
#define CLEAR system("clear")

using std::cerr;
using std::cout;
using std::endl;

Wallet::Wallet(double balance)
{
    this->balance = balance;
}

double Wallet::SetAmount()
{
    try
    {
        In amount;
        cin >> amount;
        return amount;
    }
    catch (const string msg)
    {
        using namespace NError;
        cerr << msg << ", "
             << PLEASE_INPUT_AGAIN << ". "
             << endl;
        return SetAmount();
    }
}

void Wallet::TopUp()
{
    using namespace NWallet;
    cout << TOP_UP << ": ";
    double amount = SetAmount();
    Change(amount);
}
void Wallet::Withdraw()
{
    using namespace NWallet;
    cout << WITHDRAW << ": ";
    double amount = SetAmount();
    Change(-amount);
}
void Wallet::Edit()
{
    using namespace NWallet;
    cout << EDIT << ": " << balance << " -> ";
    double amount = SetAmount();
    balance = amount;
}

void Wallet::Change(double increment)
{
    balance += increment;
}

double Wallet::GetBalance()
{
    return balance;
}