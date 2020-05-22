#include "../inc/submenu.h"

#define CLEAR system("clear")
//#define CLEAR system("cls")

extern vector<Transaction *> pTransaction;
extern vector<DepositAndLoan *> pDepoAndLoan;
extern vector<Category *> pCategory;
extern vector<Budget *> pBudget;

void AssetSubMenu::SubMenu()
{
    cout << "" << endl;
    cout << "1. " << TRANSACTION_MENU << endl
         << "2. " << DEPO_AND_LOAN_MENU << endl
         << "3. " << BUDGET_MENU << endl
         << "4. " << BACK << endl
         << DIVISION << endl;
    code = SetCode();
    if (code == 1)
    {
        TransactionMenu menu;
        menu.SubMenu();
    }
    if (code == 2)
    {
        DepositAndLoanMenu menu;
        menu.SubMenu();
    }
    if (code == 3)
    {
        BudgetMenu menu;
        menu.SubMenu();
    }
    if (code == 4)
    {
        //TODO:
    }
}

#pragma region "Protected Asset Menu"

double AssetSubMenu::SetAmount()
{
    try
    {
        cout << ">> ";
        CalcIn amount;
        cin >> amount;
        return amount;
    }
    catch (const string msg)
    {
        cerr << msg << ", "
             << PLEASE_INPUT_AGAIN << ". "
             << endl;
        return SetAmount();
    }
}

Date AssetSubMenu::SetDate()
{
    try
    {
        cout << ">> ";
        In date;
        cin >> date;
        return date;
    }
    catch (const string msg)
    {
        cerr << msg << ", "
             << PLEASE_INPUT_AGAIN << ". "
             << endl;
        return SetDate();
    }
}

void AssetSubMenu::ShowCategory()
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
Category AssetSubMenu::SetCategory()
{
    cout << ">> ";
    In n;
    cin >> n;
    try
    {
        int num = n;
        if (num <= pCategory.size() + 1)
        {
            int i = 1;
            for (auto it : pCategory)
            {
                if (i++ == num)
                {
                    return *it;
                }
            }
            cout << INPUT_NEW_CATEGORY << ": " << endl;
            cout << ">> ";
            In category;
            cin >> category;
            Category *newCate = new Category(category);
            newCate->Add();
            return *newCate;
        }
        else
        {
            cerr
                << PLEASE_INPUT_AGAIN << ". "
                << endl;
            return SetCategory();
        }
    }
    catch (const string msg)
    {
        cerr << msg << ", "
             << PLEASE_INPUT_AGAIN << ". "
             << endl;
        return SetCategory();
    }
}

Period AssetSubMenu::SetPeriod()
{
    cout << "1. " << MONTHLY << "\t\t"
         << "2. " << WEEKLY << "\t\t"
         << "3. " << DAILY << endl
         << END_OF_TITLE << endl;
    code = SetCode();
    Period period;
    if (code <= 3)
    {
        period = Period(code);
    }
    else
    {
        cerr << ERR_ILLEGAL_NUMBER << ", "
             << PLEASE_INPUT_AGAIN << ". "
             << endl;
        return SetPeriod();
    }

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
int AssetSubMenu::SetCode()
{
    try
    {
        cout << ">> ";
        In code;
        cin >> code;
        return code;
    }
    catch (const string msg)
    {
        cerr << msg << ", "
             << PLEASE_INPUT_AGAIN << ". "
             << endl;
        return SetCode();
    }
}

#pragma endregion

#pragma region "Public Transaction Menu"

void TransactionMenu::SubMenu()
{
    cout << TRANSACTION_TITLE << endl;
    cout << "1. " << ADD_SINGLE_EXPENSE << endl
         << "2. " << ADD_SINGLE_INCOME << endl
         << "3. " << ADD_REGULAR_EXPENSE << endl
         << "4. " << ADD_REGULAR_INCOME << endl
         << "5. " << EDIT_EXPENSE_AND_INCOME << endl
         << "6. " << DELETE_EXPENSE_AND_INCOME << endl
         << "7. " << BACK << endl
         << END_OF_TITLE << endl;
    code = SetCode();
    if (code == 1)
    {
        type = -1;
        InputSingleTransaction();
    }
    if (code == 2)
    {
        type = 1;
        InputSingleTransaction();
    }
    if (code == 3)
    {
        type = -1;
        InputRegularTransaction();
    }
    if (code == 4)
    {
        type = 1;
        InputRegularTransaction();
    }
    if (code == 5)
    {
        //TODO:
    }
    if (code == 6)
    {
        //TODO:
    }
    if (code == 7)
    {
        //TODO:
    }
}

void TransactionMenu::InputSingleTransaction()
{
    CLEAR;
    PrintSingleBody("?", "", "");
    amount = SetAmount();

    CLEAR;
    PrintSingleBody(amount, "?", "");
    ShowCategory();
    category = SetCategory();

    CLEAR;
    PrintSingleBody(amount, category, "?");
    date = SetDate();

    CLEAR;
    PrintSingleBody(amount, category, date);
    PrintInstruction();
    code = SetCode();

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
    amount = SetAmount();

    CLEAR;
    PrintRegularBody(amount, "?", "", "");
    ShowCategory();
    category = SetCategory();

    CLEAR;
    PrintRegularBody(amount, category, "?", "");
    date = SetDate();

    CLEAR;
    PrintRegularBody(amount, category, date, "?");
    period = SetPeriod();

    CLEAR;
    PrintRegularBody(amount, category, date, period);
    PrintInstruction();
    code = SetCode();

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
    principle = SetAmount();

    CLEAR;
    PrintDepoLoanBody(principle, "?", "", "", "", "");
    interest = SetRate();

    CLEAR;
    PrintDepoLoanBody(principle, interest, "?", "", "", "");
    start = SetDate();

    CLEAR;
    PrintDepoLoanBody(principle, interest, start, "?", "", "");
    end = SetDate();

    CLEAR;
    PrintDepoLoanBody(principle, interest, start, end, "?", "");
    period = SetPeriod();

    CLEAR;
    PrintDepoLoanBody(principle, interest, start, end, period, "?");
    info = SetInfo();

    CLEAR;
    PrintDepoLoanBody(principle, interest, start, end, period, info);
    PrintInstruction();
    code = SetCode();

    if (code == 1)
    {
        DepositAndLoan *t =
            new DepositAndLoan(principle, interest,
                               start, end,
                               period, info);
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

string DepositAndLoanMenu::SetInfo()
{
    //TODO:
    return "hellos";
}
double DepositAndLoanMenu::SetRate()
{
    try
    {
        cout << ">> ";
        In r;
        cin >> r;
        double rate = double(r);
        if (rate >= 0 || rate <= 10)
        {
            return rate;
        }
        else
        {
            cerr << "error" << endl;
            return SetRate();
        }
    }
    catch (const string msg)
    {
        cerr << msg << ", "
             << PLEASE_INPUT_AGAIN << ". "
             << endl;
        return SetRate();
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

void BudgetMenu::InputBudget()
{
    CLEAR;
    PrintBudgetBody("?", "", "");
    budget = SetAmount();

    CLEAR;
    PrintBudgetBody(budget, "?", "");
    ShowCategory();
    category = SetCategory();

    CLEAR;
    PrintBudgetBody(budget, category, "?");
    start = SetDate();

    CLEAR;
    PrintBudgetBody(budget, category, start);

    PrintInstruction();
    code = SetCode();

    if (code == 1)
    {
        Budget *t = new Budget(budget, category, start);
        t->Add();
    }
    if (code == 2)
    {
        InputBudget();
    }
    if (code == 3)
    {
        cout << "help" << endl;
    }
    if (code >= 4)
    {
        //
    }

    CLEAR;
}

void BudgetMenu::PrintAllBudget()
{
    cout << BUDGET << "\t\t"
         << CATEGORY << "\t\t"
         << START_DATE << endl;
    for (auto it : pBudget)
    {
        it->Print();
    }
}

#pragma endregion

#pragma region "Private Budget Menu"

template <typename T1, typename T2, typename T3>
void BudgetMenu::PrintBudgetBody(T1 x, T2 y, T3 z)
{
    cout << BUDGET_TITLE << endl
         << BUDGET << ": " << x << endl
         << CATEGORY << ": " << y << endl
         << START_DATE << ": " << z << endl
         << DIVISION << endl;
}

#pragma endregion

void BudgetMenu::SubMenu()
{
}
void DepositAndLoanMenu::SubMenu()
{
}