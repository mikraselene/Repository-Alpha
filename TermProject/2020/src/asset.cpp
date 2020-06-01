#include "../inc/asset.h"

std::vector<std::shared_ptr<Transaction>> pTransaction;
std::vector<std::shared_ptr<DepositAndLoan>> pDepoAndLoan;
extern std::vector<std::shared_ptr<Category>> pCategory;

#pragma region "Asset"

void Asset::SetId(const int &id)
{
    this->id = id;
}

double Asset::SetAmount() const
{
    try
    {
        std::cout << ">> ";
        CalcIn amount;
        std::cin >> amount;
        return amount;
    }
    catch (const std::string msg)
    {
        std::cerr << msg << ", "
                  << NError::PLEASE_INPUT_AGAIN << ". "
                  << std::endl;
        return SetAmount();
    }
}

Date Asset::SetDate() const
{
    try
    {
        std::cout << ">> ";
        In date;
        std::cin >> date;
        return date;
    }
    catch (const std::string msg)
    {

        std::cerr << msg << ", "
                  << NError::PLEASE_INPUT_AGAIN << ". "
                  << std::endl;
        return SetDate();
    }
}

void Asset::ShowCategory() const
{
    int i = 1;
    for (auto it = pCategory.begin(); it != pCategory.end(); it++)
    {
        std::cout << i++ << ". " << std::string(**it) << "\t\t";
        if ((i - 1) % 4 == 0)
        {
            std::cout << std::endl;
        }
    }
    std::cout << i << ". " << NCategory::ADD_NEW_CATEGORY << std::endl;
}

Category Asset::SetCategory() const
{
    std::cout << ">> ";
    In n;
    std::cin >> n;
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
            std::cout << NCategory::ADD_NEW_CATEGORY << ": " << std::endl;
            std::cout << ">> ";
            In category;
            std::cin >> category;
            std::shared_ptr<Category> newCate = std::make_shared<Category>(category);
            newCate->Add();
            return *newCate;
        }
        else
        {
            std::cerr << NError::ILLEGAL_CATEGORY << ", "
                      << NError::PLEASE_INPUT_AGAIN << ". "
                      << std::endl;
            return SetCategory();
        }
    }
    catch (const std::string msg)
    {
        std::cerr << msg << ", "
                  << NError::PLEASE_INPUT_AGAIN << ". "
                  << std::endl;
        return SetCategory();
    }
}

Period Asset::SetPeriod() const
{
    std::cout << "1. " << NPeriod::STR_MONTHLY << "\t\t"
              << "2. " << NPeriod::STR_WEEKLY << "\t\t"
              << "3. " << NPeriod::STR_DAILY << std::endl;
    int code = SetCode();
    Period period;
    if (code <= 3)
    {
        period = Period(code);
    }
    else
    {
        std::cerr << NError::ILLEGAL_NUMBER << ", "
                  << NError::PLEASE_INPUT_AGAIN << ". "
                  << std::endl;
        return SetPeriod();
    }
    return period;
}

void Asset::PrintInstruction() const
{
    std::cout << "1. " << NInstruction::COMFIRM_AND_SAVE << std::endl
              << "2. " << NInstruction::INPUT_AGAIN << std::endl
              << "3. " << NInstruction::BACK << std::endl
              << NInstruction::END << std::endl;
}

int Asset::SetCode() const
{
    try
    {
        std::cout << ">> ";
        In code;
        std::cin >> code;
        return code;
    }
    catch (const std::string msg)
    {
        std::cerr << msg << ", "
                  << NError::PLEASE_INPUT_AGAIN << ". "
                  << std::endl;
        return SetCode();
    }
}

#pragma endregion

#pragma region "Transaction"

/*---------------------------------------------------------------------------
函数: void InputSingleTransaction()

目的:
    用户手动输入单笔交易的各项信息并选择是否保存输入的信息. 
---------------------------------------------------------------------------*/
void Transaction::InputSingleTransaction(const int &type)
{
    this->type = type;
    Period period(Period::NO_PERIOD);
    this->period = period;
    std::string tempTitle;
    if (type == INCOME)
    {
        tempTitle = NTransaction::SINGLE_INCOME_TITLE;
    }
    else if (type == EXPENSE)
    {
        tempTitle = NTransaction::SINGLE_EXPENSE_TITLE;
    }

    CLEAR;
    PrintInputSingleBody(tempTitle, "?", "", "");
    amount = SetAmount();

    CLEAR;
    PrintInputSingleBody(tempTitle, amount, "?", "");
    ShowCategory();
    category = SetCategory();

    CLEAR;
    PrintInputSingleBody(tempTitle, amount, category, "?");
    date = SetDate();
    tempDate = date;

    CLEAR;
    PrintInputSingleBody(tempTitle, amount, category, date);
    PrintInstruction();
    InputSingleCode();

    CLEAR;
}

void Transaction::InputSingleCode()
{
    int code = SetCode();
    if (code == 1)
    {
        extern std::vector<std::shared_ptr<Bill>> pBill;
        std::shared_ptr<Bill> b =
            std::make_shared<Bill>(type, amount, date, category);
        b->Add();
        pTransaction.push_back(shared_from_this());
    }
    else if (code == 2)
    {
        InputSingleTransaction(type);
    }
    else if (code == 3)
    {
        extern std::shared_ptr<MainMenu> pMenu;
        pMenu->Menu();
    }
    else
    {
        std::cerr << NError::ILLEGAL_NUMBER << ", "
                  << NError::PLEASE_INPUT_AGAIN << ". "
                  << std::endl;
        InputSingleCode();
    }
}

/*---------------------------------------------------------------------------
函数: void InputRegularTransaction()

目的:
    用户手动输入定期交易的各项信息并选择是否保存输入的信息. 
---------------------------------------------------------------------------*/
void Transaction::InputRegularTransaction(const int &type)
{
    this->type = type;
    std::string tempTitle;
    if (type == INCOME)
    {
        tempTitle = NTransaction::REGULAR_INCOME_TITLE;
    }
    else if (type == EXPENSE)
    {
        tempTitle = NTransaction::REGULAR_EXPENSE_TITLE;
    }

    CLEAR;
    PrintInputRegularBody(tempTitle, "?", "", "", "");
    amount = SetAmount();

    CLEAR;
    PrintInputRegularBody(tempTitle, amount, "?", "", "");
    ShowCategory();
    category = SetCategory();

    CLEAR;
    PrintInputRegularBody(tempTitle, amount, category, "?", "");
    date = SetDate();
    tempDate = date;

    CLEAR;
    PrintInputRegularBody(tempTitle, amount, category, date, "?");
    period = SetPeriod();

    CLEAR;
    PrintInputRegularBody(tempTitle, amount, category, date, period);
    PrintInstruction();
    InputRegularCode();

    CLEAR;
}

void Transaction::InputRegularCode()
{
    int code = SetCode();
    if (code == 1)
    {
        pTransaction.push_back(shared_from_this());
    }
    else if (code == 2)
    {
        InputRegularTransaction(type);
    }
    else if (code == 3)
    {
        extern std::shared_ptr<MainMenu> pMenu;
        pMenu->Menu();
    }
    else
    {
        std::cerr << NError::ILLEGAL_NUMBER << ", "
                  << NError::PLEASE_INPUT_AGAIN << ". "
                  << std::endl;
        InputRegularCode();
    }
}

/*---------------------------------------------------------------------------
函数: void SingleSubmenu()

目的:
    用户对一个单笔交易进行操作. 
---------------------------------------------------------------------------*/
void Transaction::SingleSubmenu()
{
    CLEAR;
    extern std::string Division(const int &);
    PrintOneBody(amount, category, date);
    std::cout << "1. " << NTransaction::EDIT << std::endl
              << "2. " << NTransaction::DELETE << std::endl
              << "3. " << NTransaction::BACK << std::endl
              << Division(50) << std::endl;
    InputSingleSubmenuCode();
}

void Transaction::InputSingleSubmenuCode()
{
    int code = SetCode();
    if (code == 1)
    {
        Edit();
    }
    else if (code == 2)
    {
        Delete();
    }
    else if (code == 3)
    {
        return;
    }
    else
    {
        std::cerr << NError::ILLEGAL_NUMBER << ", "
                  << NError::PLEASE_INPUT_AGAIN << ". "
                  << std::endl;
        InputSingleSubmenuCode();
    }
}

/*---------------------------------------------------------------------------
函数: void RegularSubmenu()

目的:
    用户对一个定期交易进行操作. 
---------------------------------------------------------------------------*/
void Transaction::RegularSubmenu() const
{
    CLEAR;
    extern std::string Division(const int &);
    PrintOneBody(amount, category, date);
    std::cout << "1. " << NTransaction::DELETE << std::endl
              << "2. " << NTransaction::BACK << std::endl
              << Division(50) << std::endl;
    InputRegularSubmenuCode();
}

void Transaction::InputRegularSubmenuCode() const
{
    int code = SetCode();
    if (code == 1)
    {
        Delete();
    }
    else if (code == 2)
    {
        return;
    }
    else
    {
        std::cerr << NError::ILLEGAL_NUMBER << ", "
                  << NError::PLEASE_INPUT_AGAIN << ". "
                  << std::endl;
        InputRegularSubmenuCode();
    }
}

void Transaction::Edit()
{
    std::string temp;
    if (type == INCOME)
    {
        temp = NTransaction::REGULAR_INCOME_TITLE;
    }
    else if (type == EXPENSE)
    {
        temp = NTransaction::REGULAR_EXPENSE_TITLE;
    }
    CLEAR;
    PrintOneBody("?", category, date);
    amount = SetAmount();

    CLEAR;
    PrintOneBody(amount, "?", date);
    ShowCategory();
    category = SetCategory();

    CLEAR;
    PrintOneBody(amount, category, "?\t");
    date = SetDate();
    tempDate = date;

    CLEAR;
    PrintOneBody(amount, category, date);

    std::cout << PRESS_ANY_KEY;
    getchar();

    CLEAR;
}

void Transaction::Delete() const
{
    // 删除是修改的高级形式. --qyw
    for (auto it = pTransaction.begin(); it != pTransaction.end();)
    {
        if (*it == shared_from_this())
        {
            pTransaction.erase(it++);
            break;
        }
        else
        {
            it++;
        }
    }
    std::cout << DELETED << ". " << std::endl
              << PRESS_ANY_KEY;
    getchar();
}

void Transaction::Print() const
{
    std::string typestr;
    if (type == INCOME)
    {
        typestr = NTransaction::INCOME;
    }
    else if (type == EXPENSE)
    {
        typestr = NTransaction::EXPENSE;
    }
    std::cout << std::fixed << std::setprecision(2)
              << std::setw(12) << amount << "\t\t"
              << typestr
              << "\t\t"
              << category
              << "\t\t"
              << date
              << "\t\t"
              << period
              << std::endl
              << std::resetiosflags(std::ios::showpos);
}

void Transaction::SetData(const Transaction::DATA &data)
{
    this->type = data.type;
    this->amount = data.amount;
    this->category = data.category;
    this->date = data.date;
    this->tempDate = data.tempDate;
    this->period = data.period;
}

Transaction::DATA Transaction::GetData() const
{
    return {type,
            amount,
            category,
            date,
            tempDate,
            period};
}

template <typename T1, typename T2, typename T3>
void Transaction::PrintOneBody(const T1 &x,
                               const T2 &y,
                               const T3 &z) const
{
    extern std::string Division(const int &);
    std::cout << Division(95) << std::endl
              << NTransaction::ID << "\t"
              << std::setw(14) << NTransaction::AMOUNT << "\t\t"
              << NTransaction::TYPE << "\t\t"
              << NTransaction::CATEGORY << "\t\t"
              << NTransaction::DATE << "(" << NTransaction::START_DATE << ")\t\t"
              << NTransaction::PERIOD << std::endl
              << Division(95) << std::endl;
    std::string typestr;
    if (type == INCOME)
    {
        typestr = NTransaction::INCOME;
    }
    else if (type == EXPENSE)
    {
        typestr = NTransaction::EXPENSE;
    }
    std::cout << std::fixed << std::setprecision(2)
              << id << "\t"
              << std::setw(12) << x << "\t\t"
              << typestr << "\t\t"
              << y << "\t\t"
              << z << "\t\t"
              << period << std::endl
              << std::resetiosflags(std::ios::showpos);
    std::cout << Division(95) << std::endl;
}

template <typename T1, typename T2, typename T3>
void Transaction::PrintInputSingleBody(const std::string &title,
                                       const T1 &x,
                                       const T2 &y,
                                       const T3 &z) const
{
    extern std::string Division(const int &);
    std::cout << title << std::endl
              << NTransaction::AMOUNT << "(¥): " << x << std::endl
              << NTransaction::CATEGORY << ": " << y << std::endl
              << NTransaction::DATE << ": " << z << std::endl
              << Division(50) << std::endl;
}

template <typename T1, typename T2, typename T3, typename T4>
void Transaction::PrintInputRegularBody(const std::string &title,
                                        const T1 &x,
                                        const T2 &y,
                                        const T3 &z,
                                        const T4 &u) const
{
    extern std::string Division(const int &);
    std::cout << title << std::endl
              << NTransaction::AMOUNT << "(¥): " << x << std::endl
              << NTransaction::CATEGORY << ": " << y << std::endl
              << NTransaction::START_DATE << ": " << z << std::endl
              << NTransaction::PERIOD << ": " << u << std::endl
              << Division(50) << std::endl;
}

/*---------------------------------------------------------------------------
函数: void AddToBill()

目的:
    把一笔交易添加到账单. 
---------------------------------------------------------------------------*/
void Transaction::AddToBill(const std::shared_ptr<Date> &itDate) const
{
    std::shared_ptr<Bill> temp = std::make_shared<Bill>(type,
                                                        amount,
                                                        *itDate,
                                                        std::string(category) + " (" + NBill::REGULAR + ")");
    temp->Add();
}

Period Transaction::GetPeriod() const
{
    return period;
}

Date Transaction::GetTempDate() const
{
    return tempDate;
}

void Transaction::ResetDate()
{
    Date today;
    tempDate = today;
}

#pragma endregion

#pragma region "Deposit and Loan"

/*---------------------------------------------------------------------------
函数: void InputDepositAndLoan()

目的:
    用户手动输入存贷交易的各项信息并选择是否保存输入的信息. 
---------------------------------------------------------------------------*/
void DepositAndLoan::InputDepositAndLoan(const int &type)
{
    this->type = type;
    totalInterest = 0;

    CLEAR;
    PrintInputBody("?", "", "", "", "", "");
    principle = SetAmount();
    tempPrinciple = principle;

    CLEAR;
    PrintInputBody(principle, "?", "", "", "", "");
    rate = SetRate();

    CLEAR;
    PrintInputBody(principle, rate * 100, "?", "", "", "");
    isCompound = SetType();

    std::string interestType;
    isCompound
        ? interestType = NDepositAndLoan::COMPOUND_INTEREST
        : interestType = NDepositAndLoan::SIMPLE_INTEREST;

    CLEAR;
    PrintInputBody(principle, rate * 100, interestType, "?", "", "");
    date = SetDate();
    tempDate = date;

    CLEAR;
    PrintInputBody(principle, rate * 100, interestType, date, "?", "");
    period = SetPeriod();

    CLEAR;
    PrintInputBody(principle, rate * 100, interestType, date, period, "?");
    info = SetInfo();

    CLEAR;
    PrintInputBody(principle, rate * 100, interestType, date, period, info);
    PrintInstruction();
    InputCode();

    CLEAR;
}

void DepositAndLoan::InputCode()
{
    int code = SetCode();
    if (code == 1)
    {
        pDepoAndLoan.push_back(shared_from_this());
    }
    else if (code == 2)
    {
        InputDepositAndLoan(type);
    }
    else if (code == 3)
    {
        extern std::shared_ptr<MainMenu> pMenu;
        pMenu->Menu();
    }
    else
    {
        std::cerr << NError::ILLEGAL_NUMBER << ", "
                  << NError::PLEASE_INPUT_AGAIN << ". "
                  << std::endl;
        InputCode();
    }
}

/*---------------------------------------------------------------------------
函数: void Submenu()

目的:
    用户对一个借贷交易进行操作. 
---------------------------------------------------------------------------*/
void DepositAndLoan::Submenu() const
{
    CLEAR;
    extern std::string Division(const int &);
    extern std::vector<std::shared_ptr<DepositAndLoan>> pDepoAndLoan;
    std::cout << Division(115) << std::endl
              << NDepositAndLoan::ID << "\t"
              << std::setw(14) << NDepositAndLoan::PRINCIPLE << "\t"
              << std::setw(14) << NDepositAndLoan::INTEREST_RATE << "\t\t"
              << NDepositAndLoan::PERIOD << "\t\t"
              << NDepositAndLoan::TYPE << "\t\t"
              << NDepositAndLoan::START_DATE << "\t\t"
              << NDepositAndLoan::INFO << std::endl
              << Division(115) << std::endl;
    std::cout << id << "\t";
    Print();
    std::cout << Division(115) << std::endl;
    std::cout << "1. " << NDepositAndLoan::DELETE << std::endl
              << "2. " << NDepositAndLoan::BACK << std::endl
              << Division(50) << std::endl;
    InputSubmenuCode();
}

void DepositAndLoan::InputSubmenuCode() const
{
    int code = SetCode();
    if (code == 1)
    {
        for (auto it = pDepoAndLoan.begin(); it != pDepoAndLoan.end();)
        {
            if (*it == shared_from_this())
            {
                pDepoAndLoan.erase(it++);
                break;
            }
            else
            {
                it++;
            }
        }
        std::cout << DELETED << ". " << std::endl
                  << PRESS_ANY_KEY;
        getchar();
    }
    else if (code == 2)
    {
        return;
    }
    else
    {
        std::cerr << NError::ILLEGAL_NUMBER << ", "
                  << NError::PLEASE_INPUT_AGAIN << ". " << std::endl;
        InputSubmenuCode();
    }
}

void DepositAndLoan::Print() const
{
    std::string typestr;
    std::string intereststr;
    std::string interestFlag;
    if (type == DEPOSIT)
    {
        typestr = NDepositAndLoan::DEPOSIT;
    }
    else if (type == LOAN)
    {
        typestr = NDepositAndLoan::LOAN;
    }
    isCompound ? interestFlag = "C" : interestFlag = "S";
    std::string tempstr = std::to_string(rate * 100);
    intereststr = interestFlag + tempstr.substr(0, tempstr.size() - 4) + "%";
    std::cout << std::fixed << std::setprecision(2)
              << std::setw(12) << principle << "\t"
              << std::setw(12) << intereststr << "\t\t"
              << period << "\t\t"
              << typestr << "\t\t"
              << date << "\t\t"
              << info << std::endl;
}

void DepositAndLoan::SetData(const DATA &data)
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

DepositAndLoan::DATA DepositAndLoan::GetData() const
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

template <typename T1, typename T2, typename T3,
          typename T4, typename T5, typename T6>
void DepositAndLoan::PrintInputBody(const T1 &x,
                                    const T2 &y,
                                    const T3 &z,
                                    const T4 &u,
                                    const T5 &v,
                                    const T6 &w) const
{
    extern std::string Division(const int &);
    std::cout << NDepositAndLoan::TITLE << std::endl
              << NDepositAndLoan::PRINCIPLE << "(¥): " << x << std::endl
              << NDepositAndLoan::INTEREST_RATE << "(%): " << y << std::endl
              << NDepositAndLoan::INTEREST_TYPE << ": " << z << std::endl
              << NDepositAndLoan::START_DATE << ": " << u << std::endl
              << NDepositAndLoan::PERIOD << ": " << v << std::endl
              << NDepositAndLoan::INFO << ": " << w << std::endl
              << Division(50) << std::endl;
}

Period DepositAndLoan::GetPeriod() const
{
    return period;
}

Date DepositAndLoan::GetTempDate() const
{
    return tempDate;
}

/*---------------------------------------------------------------------------
函数: void AddToBill()

目的:
    把一笔交易添加到账单. 
---------------------------------------------------------------------------*/
void DepositAndLoan::AddToBill(const std::shared_ptr<Date> &itDate)
{
    CheckCompound();
    std::shared_ptr<Bill> temp = std::make_shared<Bill>(type,
                                                        rate * tempPrinciple,
                                                        *itDate,
                                                        info + " (" + NBill::INTEREST + ")");
    temp->Add();
    totalInterest += rate * tempPrinciple;
}

void DepositAndLoan::CheckCompound()
{
    if (isCompound)
    {
        tempPrinciple += tempPrinciple * rate;
    }
}

void DepositAndLoan::ResetDate()
{
    Date today;
    tempDate = today;
}

double DepositAndLoan::GetTotalInterest() const
{
    return type * totalInterest;
}

void DepositAndLoan::PrintTotalInterest() const
{
    std::string typestr;
    if (type == DEPOSIT)
    {
        typestr = NDepositAndLoan::DEPOSIT;
    }
    else if (type == LOAN)
    {
        typestr = NDepositAndLoan::LOAN;
    }
    std::cout << std::fixed << std::setprecision(2)
              << std::setw(12) << principle << "\t"
              << std::setw(12) << rate << "\t\t"
              << std::setw(12) << std::showpos << type * totalInterest << "\t\t"
              << std::resetiosflags(std::ios::showpos)
              << typestr << "\t\t"
              << date << "\t\t"
              << info << "\t\t" << std::endl;
}

double DepositAndLoan::SetRate() const
{
    try
    {
        std::cout << ">> ";
        In r;
        std::cin >> r;
        double rate = double(r);
        if (rate >= 0 || rate <= 10)
        {
            return rate / 100;
        }
        else
        {
            std::cerr << NError::ILLEGAL_NUMBER << ", "
                      << NError::PLEASE_INPUT_AGAIN << ". "
                      << std::endl;
            return SetRate();
        }
    }
    catch (const std::string msg)
    {
        std::cerr << msg << ", "
                  << NError::PLEASE_INPUT_AGAIN << ". "
                  << std::endl;
        return SetRate();
    }
}

bool DepositAndLoan::SetType() const
{
    try
    {
        std::cout << "1. " << NDepositAndLoan::SIMPLE_INTEREST << "\t\t"
                  << "2. " << NDepositAndLoan::COMPOUND_INTEREST << std::endl;
        std::cout << ">> ";
        In r;
        std::cin >> r;
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
            std::cerr << NError::ILLEGAL_NUMBER << ", "
                      << NError::PLEASE_INPUT_AGAIN << ". "
                      << std::endl;
            return SetType();
        }
    }
    catch (const std::string msg)
    {
        std::cerr << msg << ", "
                  << NError::PLEASE_INPUT_AGAIN << ". "
                  << std::endl;
        return SetRate();
    }
}

std::string DepositAndLoan::SetInfo() const
{
    In info;
    std::cin >> info;
    return info;
}

#pragma endregion
