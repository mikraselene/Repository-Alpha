#include "../inc/submenu.h"

#define CLEAR system("clear")
//#define CLEAR system("cls")

extern list<Transaction *> pTransaction;
extern list<DepositAndLoan *> pDepoAndLoan;
extern list<Category *> pCategory;

#pragma region "Protected Asset Menu"

double AssetSubMenu::InputAmount()
{
    try
    {
        cout << ">> ";
        string a;
        getline(cin, a);
        NumWithCalcIn t(a);
        double amount = t.ToRealWithCalc();
        return amount;
    }
    catch (const string msg)
    {
        cerr << msg << ", "
             << PLEASE_INPUT_AGAIN << ". "
             << endl;
        return InputAmount();
    }
}

Date AssetSubMenu::InputDate()
{
    try
    {
        cout << ">> ";
        string a;
        getline(cin, a);
        DateIn t(a);
        Date date = t.ToDate();
        return date;
    }
    catch (const string msg)
    {
        cerr << msg << ", "
             << PLEASE_INPUT_AGAIN << ". "
             << endl;
        return InputDate();
    }
}

string AssetSubMenu::InputPeriod()
{
    string period = "hello";
    return period;
}

void AssetSubMenu::PrintInstruction()
{
    cout << "1. " << COMFIRM_AND_SAVE << endl
         << "2. " << INPUT_AGAIN << endl
         << "3. " << HELP << endl
         << "4. " << BACK << endl
         << END_OF_TITLE << endl;
}
int AssetSubMenu::InputCode()
{
    try
    {
        cout << ">> ";
        string a;
        getline(cin, a);
        NumberIn t(a);
        int code = t.ToInt();
        return code;
    }
    catch (const string msg)
    {
        cerr << msg << ", "
             << PLEASE_INPUT_AGAIN << ". "
             << endl;
        return InputCode();
    }
}

#pragma endregion

#pragma region "Public Transaction Menu"

void TransactionMenu::InputSingleTransaction()
{
    CLEAR;
    PrintSingleBody("?", "", "");
    amount = InputAmount();

    CLEAR;
    PrintSingleBody(amount, "?", "");
    ShowCategory();
    InputCategory();

    CLEAR;
    PrintSingleBody(amount, category, "?");
    date = InputDate();

    CLEAR;
    PrintSingleBody(amount, category, date);
    PrintInstruction();
    code = InputCode();

    if (code == 1)
    {
        SingleTransaction *t = new SingleTransaction(amount, category, date);
        t->Add();
    }
    if (code == 2)
    {
        InputSingleTransaction();
    }
    if (code == 3)
    {
        cout << "help" << endl;
    }
    if (code >= 4)
    {
    }

    CLEAR;
}
void TransactionMenu::InputRegularTransaction()
{
    CLEAR;
    PrintRegularBody("?", "", "", "");
    amount = InputAmount();

    CLEAR;
    PrintRegularBody(amount, "?", "", "");
    ShowCategory();
    InputCategory();

    CLEAR;
    PrintRegularBody(amount, category, "?", "");
    date = InputDate();

    CLEAR;
    PrintRegularBody(amount, category, date, "?");
    period = InputPeriod();

    CLEAR;
    PrintRegularBody(amount, category, date, period);
    PrintInstruction();
    code = InputCode();

    if (code == 1)
    {
        RegularTransaction *t =
            new RegularTransaction(amount, category, date, period);
        t->Add();
    }
    if (code == 2)
    {
        InputRegularTransaction();
    }
    if (code == 3)
    {
        cout << "help" << endl;
    }
    if (code >= 4)
    {
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
void TransactionMenu::PrintAllRegular()
{
    cout << AMOUNT << "\t\t"
         << CATEGORY << "\t\t"
         << START_DATE << "\t\t"
         << PERIOD << endl;
    for (auto it : pTransaction)
    {
        it->Print();
    }
}

#pragma endregion

#pragma region "Private Transaction Menu"

void TransactionMenu::ShowCategory()
{
    int i = 1;
    for (auto it = pCategory.begin(); it != pCategory.end(); it++)
    {
        cout << i++ << ". " << (*it)->GetCategory() << "\t\t";
        if ((i - 1) % 4 == 0)
        {
            cout << endl;
        }
    }
    cout << i << ". " << ADD_NEW_CATEGORY << endl;
}
void TransactionMenu::InputCategory()
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
            for (auto it : pCategory)
            {
                if (i++ == num)
                {
                    category = *it;
                }
            }
        }
        else if (num == pCategory.size() + 1)
        {
            cout << ">> ";
            string a;
            getline(cin, a);
            StringIn t(a);
            Category *x = new Category(a);
            x->Add();
            category = *x;
        }
        else
        {
            cerr
                << PLEASE_INPUT_AGAIN << ". "
                << endl;
            InputCategory();
        }
    }
    catch (const string msg)
    {
        cerr << msg << ", "
             << PLEASE_INPUT_AGAIN << ". "
             << endl;
        InputCategory();
    }
}

template <typename T1, typename T2, typename T3>
void TransactionMenu::PrintSingleBody(T1 x, T2 y, T3 z)
{
    cout << SINGLE_EXPENSE_TITLE << endl
         << AMOUNT << ": " << x << endl
         << CATEGORY << ": " << y << endl
         << DATE << ": " << z << endl
         << DIVISION << endl;
}
template <typename T1, typename T2, typename T3, typename T4>
void TransactionMenu::PrintRegularBody(T1 x, T2 y, T3 z, T4 u)
{
    cout << REGULAR_EXPENSE_TITLE << endl
         << AMOUNT << ": " << x << endl
         << CATEGORY << ": " << y << endl
         << START_DATE << ": " << z << endl
         << PERIOD << ": " << u << endl
         << DIVISION << endl;
}

#pragma endregion

#pragma region "Public Deposit and Loan Menu"

void DepositAndLoanMenu::InputDepositAndLoan()
{
    CLEAR;
    PrintDepoLoanBody("?", "", "", "", "", "");
    principle = InputAmount();

    CLEAR;
    PrintDepoLoanBody(principle, "?", "", "", "", "");
    interestRate = InputRate();

    CLEAR;
    PrintDepoLoanBody(principle, interestRate, "?", "", "", "");
    start = InputDate();

    CLEAR;
    PrintDepoLoanBody(principle, interestRate, start, "?", "", "");
    end = InputDate();

    CLEAR;
    PrintDepoLoanBody(principle, interestRate, start, end, "?", "");
    period = InputPeriod();

    CLEAR;
    PrintDepoLoanBody(principle, interestRate, start, end, period, "?");
    info = InputInfo();

    CLEAR;
    PrintDepoLoanBody(principle, interestRate, start, end, period, info);
    PrintInstruction();
    code = InputCode();

    if (code == 1)
    {
        DepositAndLoan *t =
            new DepositAndLoan(principle, interestRate, start, end, period, info);
        t->Add();
    }
    if (code == 2)
    {
        InputDepositAndLoan();
    }
    if (code == 3)
    {
        cout << "help" << endl;
    }
    if (code >= 4)
    {
    }

    CLEAR;
}

void DepositAndLoanMenu::PrintAllDepositAndLoan()
{
    cout << PRINCIPLE << "\t\t"
         << INTEREST_RATE << "\t\t"
         << START_DATE << "\t\t"
         << END_DATE << "\t\t"
         << PERIOD << "\t\t"
         << INFO << "\t\t"
         << endl;
    for (auto it : pDepoAndLoan)
    {
        it->Print();
    }
}

#pragma endregion

#pragma region "Private Deposit and Loan Menu"

string DepositAndLoanMenu::InputInfo()
{
    return "hellos";
}
double DepositAndLoanMenu::InputRate()
{
    try
    {
        cout << ">> ";
        string a;
        getline(cin, a);
        NumberIn t(a);
        double rate = t.ToReal();
        if (rate >= 0 || rate <= 10)
        {
            return rate;
        }
        else
        {
            cerr << "error" << endl;
            return InputRate();
        }
    }
    catch (const string msg)
    {
        cerr << msg << ", "
             << PLEASE_INPUT_AGAIN << ". "
             << endl;
        return InputRate();
    }
}

template <typename T1, typename T2, typename T3,
          typename T4, typename T5, typename T6>
void DepositAndLoanMenu::PrintDepoLoanBody(T1 x, T2 y, T3 z, T4 u, T5 v, T6 w)
{
    cout << DEPO_AND_LOAN_TITLE << endl
         << PRINCIPLE << ": " << x << endl
         << INTEREST_RATE << ": " << y << endl
         << START_DATE << ": " << z << endl
         << END_DATE << ": " << u << endl
         << PERIOD << ":" << v << endl
         << INFO << ":" << w << endl
         << DIVISION << endl;
}

#pragma endregion

#pragma region "Public Budget Menu"

#pragma endregion

#pragma region "Private Budget Menu"

#pragma endregion
