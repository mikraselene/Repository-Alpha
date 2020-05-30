#include "../inc/asset.h"

using std::cerr;
using std::vector;
using namespace std;

vector<Transaction *> pTransaction;
vector<DepositAndLoan *> pDepoAndLoan;
extern vector<Category *> pCategory;

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
        cout << i++ << ". " << string(**it) << "\t\t";
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
    tempDate = date;

    CLEAR;
    cout << temp << endl;
    PrintSingleBody(amount, category, date);
    PrintInstruction();

    InputSingleCode();

    CLEAR;
}

TRANSACTION_DATA Transaction::GetData()
{
    return {type,
            amount,
            category,
            date,
            tempDate,
            period};
};

void Transaction::InputSingleCode()
{
    int code = SetCode();
    if (code == 1)
    {
        extern vector<Bill *> pBill;
        Bill *b = new Bill(type, amount, date, category);
        b->Add();
        pTransaction.push_back(this);
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
    tempDate = date;

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
    using namespace NTransaction;
    string typestr;
    if (type == 1)
    {
        typestr = INCOME;
    }
    else if (type == -1)
    {
        typestr = EXPENSE;
    }
    cout << std::fixed << std::setprecision(2)
         << setw(12) << amount << "\t\t"
         << typestr << "\t\t"
         << category << "\t\t"
         << date << "\t\t"
         << period << endl
         << std::resetiosflags(std::ios::showpos);
}

void Transaction::SingleSubmenu()
{
    CLEAR;
    using namespace NTransaction;
    extern string Division(int);
    PrintEdit(amount, category, date);
    cout << "1. " << EDIT << endl
         << "2. " << DELETE << endl
         << "3. " << BACK << endl
         << Division(20) << endl;

    int code = SetCode();
    if (code == 1)
    {
        Edit();
    }
    else if (code == 2)
    {
        for (auto it = pTransaction.begin(); it != pTransaction.end();)
        {
            if (*it == this)
            {
                pTransaction.erase(it++);
                break;
            }
            else
            {
                it++;
            }
        }
        cout << PRESS_ANY_KEY;
        getchar();
    }
    else if (code == 3)
    {
        return;
    }
    else
    {
        using namespace NError;
        cerr << ERR_ILLEGAL_NUMBER << ", "
             << PLEASE_INPUT_AGAIN << ". " << endl;
        SingleSubmenu();
    }
}

void Transaction::RegularSubmenu()
{
    CLEAR;
    using namespace NTransaction;
    extern string Division(int);
    PrintEdit(amount, category, date);
    cout << "1. " << DELETE << endl
         << "2. " << BACK << endl
         << Division(20) << endl;
    int code = SetCode();
    if (code == 1)
    {
        for (auto it = pTransaction.begin(); it != pTransaction.end();)
        {
            if (*it == this)
            {
                pTransaction.erase(it++);
                break;
            }
            else
            {
                it++;
            }
        }
        cout << PRESS_ANY_KEY;
        getchar();
    }
    else if (code == 2)
    {
        return;
    }
    else
    {
        using namespace NError;
        cerr << ERR_ILLEGAL_NUMBER << ", "
             << PLEASE_INPUT_AGAIN << ". " << endl;
        RegularSubmenu();
    }
}

void Transaction::Edit()
{
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
    PrintEdit("?", category, date);
    amount = SetAmount();

    CLEAR;
    PrintEdit(amount, "?", date);
    ShowCategory();
    category = SetCategory();

    CLEAR;
    PrintEdit(amount, category, "?\t");
    date = SetDate();
    tempDate = date;

    CLEAR;
    PrintEdit(amount, category, date);

    cout << PRESS_ANY_KEY;
    getchar();

    CLEAR;
}

template <typename T1, typename T2, typename T3>
void Transaction::PrintEdit(T1 x, T2 y, T3 z)
{
    extern string Division(int);
    using namespace NTransaction;
    cout << Division(95) << endl
         << ID << "\t"
         << setw(14) << AMOUNT << "\t\t"
         << TYPE << "\t\t"
         << CATEGORY << "\t\t"
         << DATE << "(" << START_DATE << ")\t\t"
         << PERIOD << endl
         << Division(95) << endl;
    string typestr;
    if (type == 1)
    {
        typestr = INCOME;
    }
    else if (type == -1)
    {
        typestr = EXPENSE;
    }
    cout << std::fixed << std::setprecision(2)
         << id << "\t"
         << setw(12) << x << "\t\t"
         << typestr << "\t\t"
         << y << "\t\t"
         << z << "\t\t"
         << period << endl
         << std::resetiosflags(std::ios::showpos);
    cout << Division(95) << endl;
}

void Transaction::SetData(TRANSACTION_DATA data)
{
    this->type = data.type;
    this->amount = data.amount;
    this->category = data.category;
    this->date = data.date;
    this->tempDate = data.tempDate;
    this->period = data.period;
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

void Transaction::AddToBill(Date *itDate)
{
    using namespace NBill;
    Bill *t =
        new Bill(type, amount, *itDate, string(category) + " (" + REGULAR + ")");
    t->Add();
}

Date Transaction::GetTempDate()
{
    return tempDate;
}

Period Transaction::GetPeriod()
{
    return period;
}

void Transaction::ResetDate()
{
    Date today;
    tempDate = today;
}

void Transaction::SetId(int id)
{
    this->id = id;
}

#pragma endregion

#pragma region "Deposit and Loan"

void DepositAndLoan::SetId(int id)
{
    this->id = id;
}

void DepositAndLoan::SetData(DEPOSIT_AND_LOAN_DATA data)
{
    this->isCompound = data.isCompound;
    this->type = data.type;
    this->principle = data.principle;
    this->tempPrinciple = data.tempPrinciple;
    this->rate = data.rate;
    this->totalInterest = data.totalInterest;
    this->date = data.date;
    this->tempDate = data.tempDate;
    this->info = data.info;
}

void DepositAndLoan::InputDepositAndLoan(int type)
{
    this->type = type;
    totalInterest = 0;

    CLEAR;
    PrintDepoLoanBody("?", "", "", "", "", "");
    principle = SetAmount();
    tempPrinciple = principle;

    CLEAR;
    PrintDepoLoanBody(principle, "?", "", "", "", "");
    rate = SetRate();

    CLEAR;
    PrintDepoLoanBody(principle, rate, "?", "", "", "");
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
    PrintDepoLoanBody(principle, rate, interestType, "?", "", "");
    date = SetDate();
    tempDate = date;

    CLEAR;
    PrintDepoLoanBody(principle, rate, interestType, date, "?", "");
    period = SetPeriod();

    CLEAR;
    PrintDepoLoanBody(principle, rate, interestType, date, period, "?");
    info = SetInfo();

    CLEAR;
    PrintDepoLoanBody(principle, rate, interestType, date, period, info);
    PrintInstruction();

    InputCode();

    CLEAR;
}

void DepositAndLoan::CheckCompound()
{
    if (isCompound)
    {
        tempPrinciple += tempPrinciple * rate;
    }
}

void DepositAndLoan::Submenu()
{
    CLEAR;
    extern string Division(int);

    extern vector<DepositAndLoan *> pDepoAndLoan;
    using namespace NDepositAndLoan;
    cout << Division(115) << endl
         << ID << "\t"
         << setw(14) << PRINCIPLE << "\t"
         << setw(14) << INTEREST_RATE << "\t\t"
         << PERIOD << "\t\t"
         << TYPE << "\t\t"
         << START_DATE << "\t\t"
         << INFO << endl
         << Division(115) << endl;

    cout << id << "\t";
    Print();

    cout << Division(115) << endl;
    cout << "1. " << DELETE << endl
         << "2. " << BACK << endl
         << Division(20) << endl;
    int code = SetCode();
    if (code == 1)
    {
        for (auto it = pDepoAndLoan.begin(); it != pDepoAndLoan.end();)
        {
            if (*it == this)
            {
                pDepoAndLoan.erase(it++);
                break;
            }
            else
            {
                it++;
            }
        }
        cout << PRESS_ANY_KEY;
        getchar();
    }
    else if (code == 2)
    {
        return;
    }
    else
    {
        using namespace NError;
        cerr << ERR_ILLEGAL_NUMBER << ", "
             << PLEASE_INPUT_AGAIN << ". " << endl;
        Submenu();
    }
}

double DepositAndLoan::GetTotalInterest()
{
    return type * totalInterest;
}

void DepositAndLoan::PrintTotalInterest()
{
    using namespace NDepositAndLoan;
    string typestr;
    if (type == 1)
    {
        typestr = DEPOSIT;
    }
    else if (type == -1)
    {
        typestr = LOAN;
    }
    cout << std::fixed << std::setprecision(2)
         << setw(12) << principle << "\t"
         << setw(12) << rate << "\t\t"
         << setw(12) << std::showpos << type * totalInterest << "\t\t"
         << std::resetiosflags(std::ios::showpos)
         << typestr << "\t\t"
         << date << "\t\t"
         << info << "\t\t" << endl;
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
    using namespace NDepositAndLoan;
    string typestr;
    string intereststr;
    string interestFlag;
    if (type == 1)
    {
        typestr = DEPOSIT;
    }
    else if (type == -1)
    {
        typestr = LOAN;
    }
    isCompound ? interestFlag = "C" : interestFlag = "S";
    string tempstr = std::to_string(rate * 100);
    intereststr = interestFlag + tempstr.substr(0, tempstr.size() - 4) + "%";
    cout << std::fixed << std::setprecision(2)
         << setw(12) << principle << "\t"
         << setw(12) << intereststr << "\t\t"
         << period << "\t\t"
         << typestr << "\t\t"
         << date << "\t\t"
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

void DepositAndLoan::AddToBill(Date *itDate)
{
    using namespace NBill;
    CheckCompound();
    Bill *t = new Bill(type, rate * tempPrinciple,
                       *itDate, info + " (" + INTEREST + ")");
    t->Add();
    totalInterest += rate * tempPrinciple;
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

DEPOSIT_AND_LOAN_DATA DepositAndLoan::GetData()
{
    return {isCompound,
            type,
            principle,
            tempPrinciple,
            rate,
            totalInterest,
            date,
            tempDate,
            period,
            info};
}

#if 0

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


string DepositAndLoan::GetInfo()
{
    return info;
}

#endif
Date DepositAndLoan::GetTempDate()
{
    return tempDate;
}

Period DepositAndLoan::GetPeriod()
{
    return period;
}

void DepositAndLoan::ResetDate()
{
    Date today;
    tempDate = today;
}

#pragma endregion
