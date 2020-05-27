#include "../inc/sub.h"

using std::cerr;
using std::vector;

vector<Transaction *> pTransaction;
vector<DepositAndLoan *> pDepoAndLoan;
extern vector<Category *> pCategory;
vector<Budget *> pBudget;

#pragma region "Asset"

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
            cerr << ERR_ILLEGAL_CATEGORY << ", "
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
    cout << "1. " << STR_MONTHLY << "\t\t"
         << "2. " << STR_WEEKLY << "\t\t"
         << "3. " << STR_DAILY << endl
         << END << endl;
    int code = SetCode();
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

#pragma region "Transaction"

void Transaction::InputSingleTransaction(int type)
{
    this->type = type;

    Period period(Period::NO_PERIOD);

    this->period = period;

    CLEAR;

    using namespace NTransaction;
    string temp;
    if (type == TransactionMenu::INCOME)
    {
        temp = SINGLE_INCOME_TITLE;
    }
    else if (type == TransactionMenu::EXPENSE)
    {
        temp = SINGLE_EXPENSE_TITLE;
    }

    cout << temp << endl;
    PrintSingleBody("?", "", "");
    amount = SetAmount();

    CLEAR;
    cout << temp << endl;
    PrintSingleBody(amount, "?", "");
    ShowCategory();
    category = SetCategory();

    CLEAR;
    cout << temp << endl;
    PrintSingleBody(amount, category, "?");
    date = SetDate();

    CLEAR;
    cout << temp << endl;
    PrintSingleBody(amount, category, date);
    PrintInstruction();

    InputSingleCode();

    CLEAR;
}

void Transaction::InputSingleCode()
{
    int code = SetCode();
    if (code == 1)
    {
        pTransaction.push_back(this);
        extern vector<Bill *> pBill;
        Bill *b = new Bill(type, amount, date, category.GetCategory());
        b->Add();
    }
    else if (code == 2)
    {
        InputSingleTransaction(type);
    }
    else if (code == 3)
    {
        //TODO:
        cout << "help" << endl;
    }
    else if (code == 4)
    {
        extern MainMenu *pMenu;
        pMenu->Menu();
    }
    else
    {
        using namespace NError;
        cerr << ERR_ILLEGAL_NUMBER << ", "
             << PLEASE_INPUT_AGAIN << ". " << endl;
        InputSingleCode();
    }
}

void Transaction::InputRegularTransaction(int type)
{
    this->type = type;

    using namespace NTransaction;
    string temp;
    if (type == TransactionMenu::INCOME)
    {
        temp = REGULAR_INCOME_TITLE;
    }
    else if (type == TransactionMenu::EXPENSE)
    {
        temp = REGULAR_EXPENSE_TITLE;
    }

    CLEAR;
    cout << temp << endl;
    PrintRegularBody("?", "", "", "");
    amount = SetAmount();

    CLEAR;
    cout << temp << endl;
    PrintRegularBody(amount, "?", "", "");
    ShowCategory();
    category = SetCategory();

    CLEAR;
    cout << temp << endl;
    PrintRegularBody(amount, category, "?", "");
    date = SetDate();

    CLEAR;
    cout << temp << endl;
    PrintRegularBody(amount, category, date, "?");
    period = SetPeriod();

    CLEAR;
    cout << temp << endl;
    PrintRegularBody(amount, category, date, period);
    PrintInstruction();

    InputRegularCode();

    CLEAR;
}

void Transaction::InputRegularCode()
{
    int code = SetCode();
    if (code == 1)
    {
        pTransaction.push_back(this);
        //TODO:
    }
    else if (code == 2)
    {
        InputRegularTransaction(type);
    }
    else if (code == 3)
    {
        //TODO:
        cout << "help" << endl;
    }
    else if (code == 4)
    {
        extern MainMenu *pMenu;
        pMenu->Menu();
    }
    else
    {
        using namespace NError;
        cerr << ERR_ILLEGAL_NUMBER << ", "
             << PLEASE_INPUT_AGAIN << ". " << endl;
        InputRegularCode();
    }
}

void Transaction::Print()
{
    cout << amount << "\t\t"
         << category << "\t\t"
         << date << "\t\t"
         << period << endl;
}

template <typename T1, typename T2, typename T3>
void Transaction::PrintSingleBody(T1 x, T2 y, T3 z)
{
    using namespace NTransaction;
    cout << AMOUNT << ": " << x << endl
         << CATEGORY << ": " << y << endl
         << DATE << ": " << z << endl
         << DIVISION << endl;
}

template <typename T1, typename T2, typename T3, typename T4>
void Transaction::PrintRegularBody(T1 x, T2 y, T3 z, T4 u)
{
    using namespace NTransaction;
    cout << AMOUNT << ": " << x << endl
         << CATEGORY << ": " << y << endl
         << START_DATE << ": " << z << endl
         << PERIOD << ": " << u << endl
         << DIVISION << endl;
}

int Transaction::GetType()
{
    return type;
}
double Transaction::GetAmount()
{
    return amount;
}
Date Transaction::GetDate()
{
    return date;
}
Period Transaction::GetPeriod()
{
    return period;
}
string Transaction::GetCategory()
{
    return category.GetCategory();
}
void Transaction::ResetDate()
{
    Date today;
    date = today;
}

#pragma endregion

#pragma region "Deposit and Loan"

void DepositAndLoan::InputDepositAndLoan(int type)
{
    this->type = type;
    totalInterest = 0;

    CLEAR;
    PrintDepoLoanBody("?", "", "", "", "", "");
    principle = SetAmount();

    CLEAR;
    PrintDepoLoanBody(principle, "?", "", "", "", "");
    interest = SetRate();

    CLEAR;
    PrintDepoLoanBody(principle, interest, "?", "", "", "");
    isCompound = SetType();
    string interestType;
    using namespace NDepositAndLoan;
    if (isCompound)
    {
        interestType = COMPOUND_INTEREST;
    }
    else
    {
        interestType = SIMPLE_INTEREST;
    }

    CLEAR;
    PrintDepoLoanBody(principle, interest, interestType, "?", "", "");
    start = SetDate();

    CLEAR;
    PrintDepoLoanBody(principle, interest, interestType, start, "?", "");
    period = SetPeriod();

    CLEAR;
    PrintDepoLoanBody(principle, interest, interestType, start, period, "?");
    info = SetInfo();

    CLEAR;
    PrintDepoLoanBody(principle, interest, interestType, start, period, info);
    PrintInstruction();

    InputCode();

    CLEAR;
}

void DepositAndLoan::Check()
{
    if (isCompound)
    {
        principle += principle * interest;
    }
}

void DepositAndLoan::ChangeTotalInterest(double sum)
{
    totalInterest += sum;
}
void DepositAndLoan::InputCode()
{
    int code = SetCode();
    if (code == 1)
    {
        pDepoAndLoan.push_back(this);
    }
    else if (code == 2)
    {
        InputDepositAndLoan(type);
    }
    else if (code == 3)
    {
        //TODO:
        cout << "help" << endl;
    }
    else if (code == 4)
    {
        extern MainMenu *pMenu;
        pMenu->Menu();
    }
    else
    {
        using namespace NError;
        cerr << ERR_ILLEGAL_NUMBER << ", "
             << PLEASE_INPUT_AGAIN << ". " << endl;
        InputCode();
    }
}

void DepositAndLoan::Print()
{
    cout << principle << "\t\t"
         << interest << "\t\t"
         << start << "\t\t"
         << period << "\t\t"
         << info << endl;
}

string DepositAndLoan::SetInfo()
{
    In info;
    cin >> info;
    return info;
}

bool DepositAndLoan::SetType()
{
    try
    {
        using namespace NDepositAndLoan;
        cout << "1. " << SIMPLE_INTEREST << "\t\t"
             << "2. " << COMPOUND_INTEREST << endl;
        cout << ">> ";
        In r;
        cin >> r;
        int type = int(r);
        if (type == 1)
        {
            return 0;
        }
        if (type == 2)
        {
            return 1;
        }
        else
        {
            using namespace NError;
            cerr << ERR_ILLEGAL_NUMBER << ", "
                 << PLEASE_INPUT_AGAIN << ". " << endl;
            return SetType();
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
            return rate / 100;
        }
        else
        {
            using namespace NError;
            cerr << ERR_ILLEGAL_NUMBER << ", "
                 << PLEASE_INPUT_AGAIN << ". " << endl;
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
         << INTEREST_TYPE << ": " << z << endl
         << START_DATE << ": " << u << endl
         << PERIOD << ":" << v << endl
         << INFO << ":" << w << endl
         << DIVISION << endl;
}

int DepositAndLoan::GetType()
{
    return type;
}
double DepositAndLoan::GetAmount()
{
    return principle;
}
double DepositAndLoan::GetRate()
{
    return interest;
}
Date DepositAndLoan::GetDate()
{
    return start;
}
Period DepositAndLoan::GetPeriod()
{
    return period;
}
string DepositAndLoan::GetInfo()
{
    return info;
}
void DepositAndLoan::ResetDate()
{
    Date today;
    start = today;
}

#pragma endregion

#pragma region "Budget"

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

    InputCode();

    CLEAR;
}

void Budget::InputCode()
{
    int code = SetCode();
    if (code == 1)
    {
        pBudget.push_back(this);
    }
    else if (code == 2)
    {
        InputBudget();
    }
    else if (code == 3)
    {
        //TODO:
        cout << "help" << endl;
    }
    else if (code == 4)
    {
        extern MainMenu *pMenu;
        pMenu->Menu();
    }
    else
    {
        using namespace NError;
        cerr << ERR_ILLEGAL_NUMBER << ", "
             << PLEASE_INPUT_AGAIN << ". " << endl;
        InputCode();
    }
}

void Budget::Print()
{
    cout << budget << "\t\t"
         << category << "\t\t"
         << start << endl;
}

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
