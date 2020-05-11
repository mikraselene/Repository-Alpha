#include <iostream>
#include "../inc/submenu.h"
#include "../inc/input.h"
#include "../inc/text.h"
#include "../inc/asset.h"
#include "../inc/category.h"

#define CLEAR system("clear")
//#define CLEAR system("cls")

#pragma region "Public TransactionMenu"

extern list<Transaction *> pTransaction;
extern list<Category *> pCategory;
void TransactionMenu::InputSingleTransaction()
{
    CLEAR;
    Print("?", "", "");
    InputAmount();

    CLEAR;
    Print(amount, "?", "");
    int i = 1;
    for (auto it = pCategory.begin(); it != pCategory.end(); it++)
    {
        cout << i++ << ". " << (*it)->GetCategory() << endl;
    }
    InputCategory();

    CLEAR;
    Print(amount, category, "?");
    InputDate();

    CLEAR;
    Print(amount, category, date);
    cout << "1. " << COMFIRM_AND_SAVE << endl
         << "2. " << INPUT_AGAIN << endl
         << "3. " << HELP << endl
         << "4. " << BACK << endl
         << END_OF_TITLE << endl
         << ">> ";
    int d;
    cin >> d;
    getchar();
    if (d == 1)
    {
        SingleTransaction *t = new SingleTransaction(amount, category, date);
        t->Add();
    }
    CLEAR;
}

void TransactionMenu::PrintAllSingle()
{
    cout << AMOUNT << "\t\t"
         << CATEGORY << "\t\t"
         << DATE << endl;
    for (auto it : pTransaction)
    {
        it->Print();
    }
}

#pragma endregion

#pragma region "Private TransactionMenu"

void TransactionMenu::InputAmount()
{
    try
    {
        cout << ">> ";
        string a;
        getline(cin, a);
        NumWithCalcIn t(a);
        amount = t.ToRealWithCalc();
    }
    catch (const string msg)
    {
        cerr << msg << ", "
             << PLEASE_INPUT_AGAIN << ": ";
        InputAmount();
    }
}
void TransactionMenu::InputDate()
{
    try
    {
        cout << ">> ";
        string a;
        getline(cin, a);
        DateIn t(a);
        date = t.ToDate();
    }
    catch (const string msg)
    {
        cerr << msg << ", "
             << PLEASE_INPUT_AGAIN << ": ";
        InputDate();
    }
}
void TransactionMenu::InputCategory()
{
    try
    {
        cout << ">> ";
        string code;
        cin >> code;
        NumberIn n(code);
        try
        {
            int num = n.ToInt();
            getchar();
            if (num <= pCategory.size())
            {
                int i = 1;
                for (auto it = pCategory.begin(); it != pCategory.end(); it++)
                {
                    if (i++ == num)
                    {
                        StringIn t((*it)->GetCategory());
                        category = t.ToString();
                    }
                }
            }
            else
            {
                string a;
                getline(cin, a);
                StringIn t(a);
                category = t.ToString();
            }
        }
        catch (const string msg)
        {
            cerr << msg << ", "
                 << PLEASE_INPUT_AGAIN << ": ";
            InputCategory();
        }
    }
    catch (const string msg)
    {
        cerr << msg << ", "
             << PLEASE_INPUT_AGAIN << ": ";
        InputCategory();
    }
}

template <typename T1, typename T2, typename T3>
void TransactionMenu::Print(T1 x, T2 y, T3 z)
{
    cout << SINGLE_EXPENSE_TITLE << endl;
    cout << AMOUNT << ": " << x << endl;
    cout << CATEGORY << ": " << y << endl;
    cout << DATE << ": " << z << endl;
    cout << DIVISION << endl;
}

#pragma endregion
