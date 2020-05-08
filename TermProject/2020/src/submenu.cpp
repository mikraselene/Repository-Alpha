#include <iostream>
#include "../inc/submenu.h"
#include "../inc/input.h"

void TransactionMenu::InputAmount()
{
    try
    {
        string a;
        getline(cin, a);
        Input x(a);
        cout << x.InputRealWithCalc() << endl;
    }
    catch (const string msg)
    {
        cerr << msg << endl;
        InputAmount();
    }
}