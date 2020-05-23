#include "../inc/sub.h"

#define CLEAR system("clear")
//#define CLEAR system("cls")

using std::cerr;
using std::vector;

vector<Transaction *> pTransaction;
vector<DepositAndLoan *> pDepoAndLoan;
extern vector<Category *> pCategory;
vector<Budget *> pBudget;

#pragma region "Protected Asset Menu"

double Asset::SetAmount()
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
        using namespace NError;
        cerr << msg << ", "
             << PLEASE_INPUT_AGAIN << ". "
             << endl;
        return SetAmount();
    }
}

Date Asset::SetDate()
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
        using namespace NError;
        cerr << msg << ", "
             << PLEASE_INPUT_AGAIN << ". "
             << endl;
        return SetDate();
    }
}

void Asset::ShowCategory()
{
    using namespace NCategory;
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

Category Asset::SetCategory()
{
    using namespace NCategory;
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
            cout << ADD_NEW_CATEGORY << ": " << endl;
            cout << ">> ";
            In category;
            cin >> category;
            Category *newCate = new Category(category);
            newCate->Add();
            return *newCate;
        }
        else
        {
            using namespace NError;
            cerr
                << PLEASE_INPUT_AGAIN << ". "
                << endl;
            return SetCategory();
        }
    }
    catch (const string msg)
    {
        using namespace NError;
        cerr << msg << ", "
             << PLEASE_INPUT_AGAIN << ". "
             << endl;
        return SetCategory();
    }
}

Period Asset::SetPeriod()
{
    using namespace NPeriod;
    cout << "1. " << MONTHLY << "\t\t"
         << "2. " << WEEKLY << "\t\t"
         << "3. " << DAILY << endl
         << END << endl;
    code = SetCode();
    Period period;
    if (code <= 3)
    {
        period = Period(code);
    }
    else
    {
        using namespace NError;
        cerr << ERR_ILLEGAL_NUMBER << ", "
             << PLEASE_INPUT_AGAIN << ". "
             << endl;
        return SetPeriod();
    }

    return period;
}

void Asset::PrintInstruction()
{
    using namespace NInstruction;
    cout << "1. " << COMFIRM_AND_SAVE << endl
         << "2. " << INPUT_AGAIN << endl
         << "3. " << HELP << endl
         << "4. " << BACK << endl
         << END << endl;
}

int Asset::SetCode()
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
        using namespace NError;
        cerr << msg << ", "
             << PLEASE_INPUT_AGAIN << ". "
             << endl;
        return SetCode();
    }
}

#pragma endregion

#pragma region "Public Transaction Menu"

void Transaction::InputSingleTransaction(int type)
{
    this->type = type;
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
        pTransaction.push_back(this);
    }
    if (code == 2)
    {
        InputSingleTransaction(type);
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
void Transaction::InputRegularTransaction(int type)
{
    this->type = type;
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
        pTransaction.push_back(this);
    }
    if (code == 2)
    {
        InputRegularTransaction(type);
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

void Transaction::Print()
{
    cout << amount << "\t\t"
         << category << "\t\t"
         << date << endl;
}
void Transaction::PrintAll()
{
    //TODO:
    //NOT GOOD!!
    using namespace NTransaction;
    cout << AMOUNT << "\t\t"
         << CATEGORY << "\t\t"
         << DATE << endl;
    for (auto it : pTransaction)
    {
        it->Print();
    }
}

#pragma endregion

#pragma region "Private Transaction"

template <typename T1, typename T2, typename T3>
void Transaction::PrintSingleBody(T1 x, T2 y, T3 z)
{
    using namespace NTransaction;
    cout << SINGLE_EXPENSE_TITLE << endl
         << AMOUNT << ": " << x << endl
         << CATEGORY << ": " << y << endl
         << DATE << ": " << z << endl
         << DIVISION << endl;
}
template <typename T1, typename T2, typename T3, typename T4>
void Transaction::PrintRegularBody(T1 x, T2 y, T3 z, T4 u)
{
    using namespace NTransaction;
    cout << REGULAR_EXPENSE_TITLE << endl
         << AMOUNT << ": " << x << endl
         << CATEGORY << ": " << y << endl
         << START_DATE << ": " << z << endl
         << PERIOD << ": " << u << endl
         << DIVISION << endl;
}

#pragma endregion

#pragma region "Public Deposit and Loan Menu"

void DepositAndLoan::InputDepositAndLoan()
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
        pDepoAndLoan.push_back(this);
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

void DepositAndLoan::Print()
{
}
void DepositAndLoan::PrintAll()
{
    using namespace NDepositAndLoan;
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

string DepositAndLoan::SetInfo()
{
    //TODO:
    return "hellos";
}
double DepositAndLoan::SetRate()
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
        using namespace NError;
        cerr << msg << ", "
             << PLEASE_INPUT_AGAIN << ". "
             << endl;
        return SetRate();
    }
}

template <typename T1, typename T2, typename T3,
          typename T4, typename T5, typename T6>
void DepositAndLoan::PrintDepoLoanBody(T1 x, T2 y, T3 z, T4 u, T5 v, T6 w)
{
    using namespace NDepositAndLoan;
    cout << TITLE << endl
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

void Budget::InputBudget()
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
        pBudget.push_back(this);
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

void Budget::Print()
{
}
void Budget::PrintAll()
{
    using namespace NBudget;
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
void Budget::PrintBudgetBody(T1 x, T2 y, T3 z)
{
    using namespace NBudget;
    cout << TITLE << endl
         << BUDGET << ": " << x << endl
         << CATEGORY << ": " << y << endl
         << START_DATE << ": " << z << endl
         << DIVISION << endl;
}

#pragma endregion
