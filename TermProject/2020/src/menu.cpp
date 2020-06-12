#include "../inc/menu.h"

std::shared_ptr<MainMenu> pMenu = std::make_shared<MainMenu>();

std::string Division(const int &n)
{
    std::string s(n, '-');
    return s;
}

void MainMenu::Menu() const
{
    CLEAR;
    Refresh();
    std::cout << NMenu::TITLE << std::endl
              << "1. " << NMenu::ASSET_MENU << std::endl
              << "2. " << NMenu::BILL_MENU << std::endl
              << "3. " << NMenu::WALLET_MENU << std::endl
              << "4. " << NMenu::FILE_MENU << std::endl
              << "5. " << NMenu::EXIT << std::endl
              << NMenu::END << std::endl;
    InputCode();
}

void MainMenu::InputCode() const
{
    int code = SetCode();
    if (code == 1)
    {
        std::shared_ptr<MainMenu> pMenu = std::make_shared<AssetMenu>();
        pMenu->Menu();
    }
    else if (code == 2)
    {
        std::shared_ptr<MainMenu> pMenu = std::make_shared<BillMenu>();
        pMenu->Menu();
    }
    else if (code == 3)
    {
        std::shared_ptr<MainMenu> pMenu = std::make_shared<WalletMenu>();
        pMenu->Menu();
    }
    else if (code == 4)
    {
        std::shared_ptr<MainMenu> pMenu = std::make_shared<FileMenu>();
        pMenu->Menu();
    }
    else if (code == 5)
    {
        return;
    }
    else
    {
        std::cerr << NError::ILLEGAL_NUMBER << ", "
                  << NError::PLEASE_INPUT_AGAIN << ". "
                  << std::endl;
        InputCode();
    }
}

int MainMenu::SetCode() const
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

void AssetMenu::Menu() const
{
    CLEAR;
    std::cout << NMenu::ASSET_TITLE << std::endl
              << "1. " << NMenu::TRANSACTION_MENU << std::endl
              << "2. " << NMenu::DEPO_AND_LOAN_MENU << std::endl
              << "3. " << NMenu::BACK << std::endl
              << NMenu::END << std::endl;

    InputCode();
}

void AssetMenu::InputCode() const
{
    int code = SetCode();
    if (code == 1)
    {
        std::shared_ptr<MainMenu> pMenu = std::make_shared<TransactionMenu>();
        pMenu->Menu();
    }
    else if (code == 2)
    {
        std::shared_ptr<MainMenu> pMenu = std::make_shared<DepositAndLoanMenu>();
        pMenu->Menu();
    }
    else if (code == 3)
    {
        std::shared_ptr<MainMenu> pMenu = std::make_shared<MainMenu>();
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

void AssetMenu::PrintAll() const
{
}

#pragma region "Asset"

void TransactionMenu::Menu() const
{
    CLEAR;
    Refresh();
    std::cout << NMenu::TRANSACTION_TITLE << std::endl
              << "1. " << NMenu::ADD_SINGLE_EXPENSE << std::endl
              << "2. " << NMenu::ADD_SINGLE_INCOME << std::endl
              << "3. " << NMenu::ADD_REGULAR_EXPENSE << std::endl
              << "4. " << NMenu::ADD_REGULAR_INCOME << std::endl
              << "5. " << NMenu::EDIT_TRANSACTION << std::endl
              << "6. " << NMenu::BACK << std::endl
              << NMenu::END << std::endl;

    InputCode();
}

void TransactionMenu::InputCode() const
{
    int code = SetCode();
    if (code == 1)
    {
        std::shared_ptr<Transaction> p = std::make_shared<Transaction>();
        p->InputSingleTransaction(EXPENSE);
        std::shared_ptr<MainMenu> pMenu = std::make_shared<TransactionMenu>();
        pMenu->Menu();
    }
    else if (code == 2)
    {
        std::shared_ptr<Transaction> p = std::make_shared<Transaction>();
        p->InputSingleTransaction(INCOME);
        std::shared_ptr<MainMenu> pMenu = std::make_shared<TransactionMenu>();
        pMenu->Menu();
    }
    else if (code == 3)
    {
        std::shared_ptr<Transaction> p = std::make_shared<Transaction>();
        p->InputRegularTransaction(EXPENSE);
        std::shared_ptr<MainMenu> pMenu = std::make_shared<TransactionMenu>();
        pMenu->Menu();
    }
    else if (code == 4)
    {
        std::shared_ptr<Transaction> p = std::make_shared<Transaction>();
        p->InputRegularTransaction(INCOME);
        std::shared_ptr<MainMenu> pMenu = std::make_shared<TransactionMenu>();
        pMenu->Menu();
    }
    else if (code == 5)
    {
        EditTransaction();
        std::shared_ptr<MainMenu> pMenu = std::make_shared<TransactionMenu>();
        pMenu->Menu();
    }
    else if (code == 6)
    {
        std::shared_ptr<MainMenu> pMenu = std::make_shared<AssetMenu>();
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

void TransactionMenu::PrintAll() const
{
    CLEAR;
    extern std::vector<std::shared_ptr<Transaction>> pTransaction;
    std::cout << Division(95) << std::endl
              << NTransaction::ID << "\t"
              << std::setw(14) << NTransaction::AMOUNT << "\t\t"
              << NTransaction::TYPE << "\t\t"
              << NTransaction::CATEGORY << "\t\t"
              << NTransaction::DATE << "(" << NTransaction::START_DATE << ")\t\t"
              << NTransaction::PERIOD << std::endl
              << Division(95) << std::endl;

    for (int i = 0; i < pTransaction.size(); i++)
    {
        std::cout << i + 1 << "\t";
        pTransaction[i]->SetId(i + 1);
        pTransaction[i]->Print();
    }
    std::cout << Division(95) << std::endl;
}

void TransactionMenu::EditTransaction() const
{
    CLEAR;
    PrintAll();
    std::cout << NTransaction::CHOOSE_A_TRANSACTION << ", "
              << NTransaction::PRESS_ENTER_TO_EXIT << ". " << std::endl;
    InputEditCode();
}

void TransactionMenu::InputEditCode() const
{
    int code = SetCode();
    extern std::vector<std::shared_ptr<Transaction>> pTransaction;
    if (code >= 1 && code <= pTransaction.size())
    {
        pTransaction[code - 1]->GetPeriod() == Period::NO_PERIOD
            ? pTransaction[code - 1]->SingleSubmenu()
            : pTransaction[code - 1]->RegularSubmenu();
        EditTransaction();
    }
    else if (code == 0)
    {
        return;
    }
    else
    {
        std::cerr << NError::ILLEGAL_NUMBER << ", "
                  << NError::PLEASE_INPUT_AGAIN << ". "
                  << std::endl;
        InputEditCode();
    }
}

void DepositAndLoanMenu::Menu() const
{
    CLEAR;
    Refresh();
    std::cout << NMenu::DEPO_AND_LOAN_TITLE << std::endl
              << "1. " << NMenu::ADD_DEPOSIT << std::endl
              << "2. " << NMenu::ADD_LOAN << std::endl
              << "3. " << NMenu::EDIT << std::endl
              << "4. " << NMenu::STATISTICS << std::endl
              << "5. " << NMenu::BACK << std::endl
              << NMenu::END << std::endl;
    InputCode();
}

void DepositAndLoanMenu::InputCode() const
{
    int code = SetCode();
    if (code == 1)
    {
        std::shared_ptr<DepositAndLoan> p = std::make_shared<DepositAndLoan>();
        p->InputDepositAndLoan(DEPOSIT);
        std::shared_ptr<MainMenu> pMenu = std::make_shared<DepositAndLoanMenu>();
        pMenu->Menu();
    }
    else if (code == 2)
    {
        std::shared_ptr<DepositAndLoan> p = std::make_shared<DepositAndLoan>();
        p->InputDepositAndLoan(LOAN);
        std::shared_ptr<MainMenu> pMenu = std::make_shared<DepositAndLoanMenu>();
        pMenu->Menu();
    }
    else if (code == 3)
    {
        EditDepositAndLoan();
        std::shared_ptr<MainMenu> pMenu = std::make_shared<DepositAndLoanMenu>();
        pMenu->Menu();
    }
    else if (code == 4)
    {
        GetStats();
        std::shared_ptr<MainMenu> pMenu = std::make_shared<DepositAndLoanMenu>();
        pMenu->Menu();
    }
    else if (code == 5)
    {
        std::shared_ptr<MainMenu> pMenu = std::make_shared<AssetMenu>();
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

void DepositAndLoanMenu::PrintAll() const
{
    CLEAR;

    extern std::vector<std::shared_ptr<DepositAndLoan>> pDepoAndLoan;
    std::cout << Division(115) << std::endl
              << NDepositAndLoan::ID << "\t"
              << std::setw(14) << NDepositAndLoan::PRINCIPLE << "\t"
              << std::setw(14) << NDepositAndLoan::INTEREST_RATE << "*\t\t"
              << NDepositAndLoan::PERIOD << "\t\t"
              << NDepositAndLoan::TYPE << "\t\t"
              << NDepositAndLoan::START_DATE << "\t\t"
              << NDepositAndLoan::INFO << std::endl
              << Division(115) << std::endl;
    for (int i = 0; i < pDepoAndLoan.size(); i++)
    {
        std::cout << i + 1 << "\t";
        pDepoAndLoan[i]->SetId(i + 1);
        pDepoAndLoan[i]->Print();
    }
    std::cout << Division(115) << std::endl;
    std::cout << "* " << NDepositAndLoan::RATE_HELP << std::endl;
}

void DepositAndLoanMenu::EditDepositAndLoan() const
{
    CLEAR;
    PrintAll();
    std::cout << NDepositAndLoan::CHOOSE_A_DEPOSIT_OR_LOAN << ", "
              << NDepositAndLoan::PRESS_ENTER_TO_EXIT << ". " << std::endl;
    InputEditCode();
}

void DepositAndLoanMenu::InputEditCode() const
{
    int code = SetCode();
    extern std::vector<std::shared_ptr<DepositAndLoan>> pDepoAndLoan;
    if (code >= 1 && code <= pDepoAndLoan.size())
    {
        pDepoAndLoan[code - 1]->Submenu();
        EditDepositAndLoan();
    }
    else if (code == 0)
    {
        return;
    }
    else
    {
        std::cerr << NError::ILLEGAL_NUMBER << ", "
                  << NError::PLEASE_INPUT_AGAIN << ". "
                  << std::endl;
        InputEditCode();
    }
}

void DepositAndLoanMenu::GetStats() const
{
    CLEAR;
    extern std::vector<std::shared_ptr<DepositAndLoan>> pDepoAndLoan;
    double totalIncome = 0;
    double totalExpense = 0;
    std::cout << Division(125) << std::endl
              << NDepositAndLoan::ID << "\t"
              << std::setw(14) << NDepositAndLoan::PRINCIPLE << "\t"
              << std::setw(14) << NDepositAndLoan::INTEREST_RATE << "\t\t"
              << std::setw(16) << NDepositAndLoan::TOTAL_INTEREST << "\t\t"
              << NDepositAndLoan::TYPE << "\t\t"
              << NDepositAndLoan::START_DATE << "\t\t"
              << NDepositAndLoan::INFO << std::endl
              << Division(125) << std::endl;
    for (int i = 0; i < pDepoAndLoan.size(); i++)
    {
        std::cout << i + 1 << "\t";
        pDepoAndLoan[i]->PrintTotalInterest();
        double temp = pDepoAndLoan[i]->GetTotalInterest();
        temp > 0 ? totalIncome += temp : totalExpense += temp;
    }
    std::cout << Division(125) << std::endl
              << std::fixed << std::setprecision(2)
              << NDepositAndLoan::TOTAL_INCOME << ": "
              << abs(totalIncome) << NDepositAndLoan::YUAN << std::endl
              << NDepositAndLoan::TOTAL_EXPENSE << ": "
              << abs(totalExpense) << NDepositAndLoan::YUAN << std::endl
              << NSystem::PRESS_ANY_KEY;
    getchar();
}

#pragma endregion

#pragma region "Bill"

void BillMenu::Menu() const
{
    CLEAR;
    std::cout << NMenu::BILL_TITLE << std::endl
              << "1. " << NMenu::OVERVIEW << std::endl
              << "2. " << NMenu::FILTER << std::endl
              << "3. " << NMenu::STATISTICS << std::endl
              << "4. " << NMenu::BACK << std::endl
              << NMenu::END << std::endl;
    InputCode();
}

void BillMenu::InputCode() const
{
    int code = SetCode();
    if (code == 1)
    {
        std::shared_ptr<MainMenu> pMenu = std::make_shared<OverviewMenu>();
        pMenu->Menu();
    }
    else if (code == 2)
    {
        std::shared_ptr<MainMenu> pMenu = std::make_shared<FilterMenu>();
        pMenu->Menu();
    }
    else if (code == 3)
    {
        std::shared_ptr<MainMenu> pMenu = std::make_shared<StatisticsMenu>();
        pMenu->Menu();
    }
    else if (code == 4)
    {
        std::shared_ptr<MainMenu> pMenu = std::make_shared<MainMenu>();
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

void OverviewMenu::Menu() const
{
    CLEAR;
    extern std::vector<std::shared_ptr<Bill>> pBill;
    std::vector<std::shared_ptr<Bill>> temp(pBill);

    std::cout << NMenu::OVERVIEW_TITLE << std::endl
              << "1. " << NMenu::BY_DATE << "(" << NMenu::DESCEND << ")" << std::endl
              << "2. " << NMenu::BY_DATE << "(" << NMenu::ASCEND << ")" << std::endl
              << "3. " << NMenu::BY_AMOUNT << "(" << NMenu::DESCEND << ")" << std::endl
              << "4. " << NMenu::BY_AMOUNT << "(" << NMenu::ASCEND << ")" << std::endl
              << "5. " << NMenu::BACK << std::endl
              << NMenu::OVERVIEW_END
              << std::endl;
    InputCode();
}

void OverviewMenu::InputCode() const
{
    int code = SetCode();
    if (code <= 4 && code >= 1)
    {
        std::shared_ptr<MainMenu> pMenu = std::make_shared<OverviewMenu>();
        PrintAll(code);
        pMenu->Menu();
    }
    else if (code == 5)
    {
        std::shared_ptr<MainMenu> pMenu = std::make_shared<BillMenu>();
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

void OverviewMenu::PrintAll(const int &flag) const
{
    CLEAR;
    extern std::vector<std::shared_ptr<Bill>> pBill;
    std::vector<std::shared_ptr<Bill>> temp(pBill);

    if (flag == 1)
    {
        sort(temp.begin(), temp.end(),
             [](std::shared_ptr<Bill> A, std::shared_ptr<Bill> B) {
                 return A->GetDate() > B->GetDate();
             });
    }
    else if (flag == 2)
    {
        sort(temp.begin(), temp.end(),
             [](std::shared_ptr<Bill> A, std::shared_ptr<Bill> B) {
                 return A->GetDate() < B->GetDate();
             });
    }
    else if (flag == 3)
    {
        sort(temp.begin(), temp.end(),
             [](std::shared_ptr<Bill> A, std::shared_ptr<Bill> B) {
                 return A->GetAmount() > B->GetAmount();
             });
    }
    else if (flag == 4)
    {
        sort(temp.begin(), temp.end(),
             [](std::shared_ptr<Bill> A, std::shared_ptr<Bill> B) {
                 return A->GetAmount() < B->GetAmount();
             });
    }

    std::cout << Division(90) << std::endl
              << std::setw(12) << NBill::AMOUNT << "\t"
              << NBill::TYPE << "\t\t\t"
              << NBill::DATE << "\t\t\t"
              << NBill::INFO << std::endl
              << Division(90) << std::endl;
    for (auto it : temp)
    {
        it->Print();
    }
    std::cout << Division(90) << std::endl
              << NSystem::PRESS_ANY_KEY;
    getchar();
}

void FilterMenu::Menu() const
{
    CLEAR;
    std::cout << NMenu::FILTER_TITLE << std::endl
              << "1. " << NMenu::FILTER_BY_AMOUNT << std::endl
              << "2. " << NMenu::FILTER_BY_DATE << std::endl
              << "3. " << NMenu::FILTER_BY_TYPE << std::endl
              << "4. " << NMenu::BACK << std::endl
              << NMenu::END << std::endl;
    InputCode();
}

void FilterMenu::InputCode() const
{
    int code = SetCode();
    if (code == 1)
    {
        FilterByAmount();
        PrintFiltered();
        Menu();
    }
    else if (code == 2)
    {
        FilterByDate();
        PrintFiltered();
        Menu();
    }
    else if (code == 3)
    {
        FilterByType();
        PrintFiltered();
        Menu();
    }
    else if (code == 4)
    {
        std::shared_ptr<MainMenu> pMenu = std::make_shared<BillMenu>();
        pMenu->Menu();
    }
    else
    {
        std::cerr << NError::ILLEGAL_NUMBER << ", "
                  << NError::PLEASE_INPUT_AGAIN << ". "
                  << std::endl;
        return InputCode();
    }
}

void FilterMenu::PrintFiltered() const
{
    CLEAR;
    extern std::vector<std::shared_ptr<Bill>> pFiltered;
    std::cout << Division(90) << std::endl
              << std::setw(12) << NBill::AMOUNT << "\t"
              << NBill::TYPE << "\t\t\t"
              << NBill::DATE << "\t\t\t"
              << NBill::INFO << std::endl
              << Division(90) << std::endl;
    for (auto it : pFiltered)
    {
        it->Print();
    }
    std::cout << Division(90) << std::endl
              << NSystem::PRESS_ANY_KEY;
    getchar();
}

double FilterMenu::SetAmount() const
{
    try
    {
        std::cout << ">> ";
        In amount;
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

Date FilterMenu::SetDate() const
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

int FilterMenu::SetType() const
{
    try
    {
        std::cout << ">> ";
        In code;
        std::cin >> code;
        if (int(code) == 1 || int(code) == 2)
        {
            return code;
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
        return SetType();
    }
}

void FilterMenu::FilterByAmount() const
{
    CLEAR;
    PrintFilterBody("?", "");
    double lowerLimit = SetAmount();

    CLEAR;
    PrintFilterBody(lowerLimit, "?");
    double upperLimit = SetAmount();

    CLEAR;
    PrintFilterBody(lowerLimit, upperLimit);
    Filter filter;
    filter.FilterByAmount(lowerLimit, upperLimit);
    extern std::vector<std::shared_ptr<Bill>> pFiltered;
    sort(pFiltered.begin(), pFiltered.end(),
         [](std::shared_ptr<Bill> A, std::shared_ptr<Bill> B) {
             return A->GetAmount() > B->GetAmount();
         });
}

void FilterMenu::FilterByDate() const
{
    CLEAR;
    PrintFilterBody("?", "");
    Date lowerLimit = SetDate();

    CLEAR;
    PrintFilterBody(lowerLimit, "?");
    Date upperLimit = SetDate();

    CLEAR;
    PrintFilterBody(lowerLimit, upperLimit);
    Filter filter;
    filter.FilterByDate(lowerLimit, upperLimit);
    extern std::vector<std::shared_ptr<Bill>> pFiltered;
    sort(pFiltered.begin(), pFiltered.end(),
         [](std::shared_ptr<Bill> A, std::shared_ptr<Bill> B) {
             return A->GetDate() > B->GetDate();
         });
}

void FilterMenu::FilterByType() const
{
    std::cout << "1. " << NBill::INCOME << std::endl
              << "2." << NBill::EXPENSE << std::endl;
    int code = SetType();
    if (code == 1)
    {
        Filter filter;
        filter.FilterByType(Bill::INCOME);
    }
    else if (code == 2)
    {
        Filter filter;
        filter.FilterByType(Bill::EXPENSE);
    }
}

template <typename T1, typename T2>
void FilterMenu::PrintFilterBody(const T1 &x, const T2 &y) const
{
    std::cout << Division(50) << std::endl
              << NMenu::LOWER_LIMIT << ": " << x << std::endl
              << NMenu::UPPER_LIMIT << ": " << y << std::endl
              << Division(50) << std::endl;
}

void StatisticsMenu::Menu() const
{
    CLEAR;
    extern std::vector<std::shared_ptr<Bill>> pBill;
    sort(pBill.begin(), pBill.end(),
         [](std::shared_ptr<Bill> A, std::shared_ptr<Bill> B) {
             return A->GetDate() < B->GetDate();
         });
    Date today;
    int currentYear = today.GetYear();
    int currentMonth = today.GetMonth();
    int firstYear = pBill[0]->GetDate().GetYear();
    int firstMonth = pBill[0]->GetDate().GetMonth();
    int totalMonth = (currentYear - firstYear) * 12 + (currentMonth - firstMonth);

    std::vector<BILL_BY_MONTH> y(totalMonth + 1, {0, 0, 0});

    int monthCount = 0;
    for (int i = 0; i < pBill.size(); i++)
    {
        if (pBill[i]->GetType() == Bill::EXPENSE)
        {
            y[monthCount].amount += pBill[i]->GetAmount();
        }
        if (i != pBill.size() - 1)
        {
            if (pBill[i + 1]->GetDate().GetYear() != pBill[i]->GetDate().GetYear() ||
                pBill[i + 1]->GetDate().GetMonth() != pBill[i]->GetDate().GetMonth())
            {
                y[monthCount].year = pBill[i]->GetDate().GetYear();
                y[monthCount].month = pBill[i]->GetDate().GetMonth();
                monthCount++;
            }
        }
    }

    std::vector<double> monthAmount(totalMonth);

    for (int i = 0; i < totalMonth; i++)
    {
        monthAmount[i] = y[i].amount;
    }
    LeastSquare ls(monthAmount);
    ls.Fitting();
    double fit = ls.Y(totalMonth + 1);

    monthAmount.push_back(y[totalMonth].amount);

    double sum = accumulate(monthAmount.begin(), monthAmount.end(), 0);
    double max = *max_element(monthAmount.begin(), monthAmount.end());

    monthAmount[totalMonth] = fit;

    for (int i = 0; i < totalMonth; i++)
    {
        std::cout << y[i].year << "."
                  << std::setw(2) << std::setfill('0') << y[i].month << ", "
                  << std::setfill(' ')
                  << std::fixed << std::setprecision(2)
                  << y[i].amount << NBill::YUAN << " " << std::endl;

        for (int j = 0; j < monthAmount[i] * 30 / max; j++)
        {
            std::cout << "\033[47m \033[0m";
        }

        std::cout << std::endl;
    }

    std::cout << currentYear << "."
              << std::setw(2) << std::setfill('0') << currentMonth << ", "
              << std::setfill(' ');

    std::cout << std::fixed << std::setprecision(2)
              << y[totalMonth].amount << NBill::YUAN << " " << std::endl;

    if (y[totalMonth].amount / fit < 1)
    {
        for (int j = 0; j < monthAmount[totalMonth] * 30 / max; j++)
        {
            if (j < (monthAmount[totalMonth] * 30 / max) * y[totalMonth].amount / fit)
            {
                std::cout << "\033[42m \033[0m";
            }
            else
            {
                std::cout << "\033[47m  \033[0m";
            }
        }
    }
    else
    {
        for (int j = 0;
             j < (monthAmount[totalMonth] * 30 / max) * y[totalMonth].amount / fit;
             j++)
        {
            if (j <= int(monthAmount[totalMonth] * 30 / max))
            {
                std::cout << "\033[47m  \033[0m";
            }
            else
            {
                std::cout << "\033[41m  \033[0m";
            }
        }
    }
    std::cout << std::endl;

    std::cout << Division(50) << std::endl
              << NBill::EXPECTED << fit << NBill::YUAN << ", "
              << NBill::USED << y[totalMonth].amount * 100 / fit << "%. " << std::endl;

    std::cout << NSystem::PRESS_ANY_KEY;
    getchar();
    std::shared_ptr<MainMenu> pMenu = std::make_shared<BillMenu>();
    pMenu->Menu();
}

#pragma endregion

#pragma region "Else"

extern std::shared_ptr<Wallet> pWallet;

void WalletMenu::Menu() const
{
    CLEAR;
    std::cout << NWallet::TITLE << std::endl
              << NWallet::BALANCE << ": " << pWallet->GetBalance() << std::endl;
    if (pWallet->GetBalance() < 0)
    {
        std::cout << "[" << NWallet::NEGATIVE_BALANCE_WARNING << "]"
                  << std::endl;
    }
    std::cout << "1. " << NWallet::TOP_UP << std::endl
              << "2. " << NWallet::WITHDRAW << std::endl
              << "3. " << NWallet::EDIT << std::endl
              << "4. " << NWallet::BACK << std::endl
              << NWallet::END << std::endl;
    InputCode();
}

void WalletMenu::InputCode() const
{
    int code = SetCode();
    if (code == 1)
    {
        pWallet->TopUp();
        std::shared_ptr<MainMenu> pMenu = std::make_shared<WalletMenu>();
        pMenu->Menu();
    }
    else if (code == 2)
    {
        pWallet->Withdraw();
        std::shared_ptr<MainMenu> pMenu = std::make_shared<WalletMenu>();
        pMenu->Menu();
    }
    else if (code == 3)
    {
        pWallet->Edit();
        std::shared_ptr<MainMenu> pMenu = std::make_shared<WalletMenu>();
        pMenu->Menu();
    }
    else if (code == 4)
    {
        std::shared_ptr<MainMenu> pMenu = std::make_shared<MainMenu>();
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

void FileMenu::Menu() const
{
    CLEAR;
    std::cout << NFile::TITLE << std::endl
              << "1. " << NFile::SAVE << std::endl
              << "2. " << NFile::LOAD << std::endl
              << "3. " << NFile::BACK << std::endl
              << NFile::END << std::endl;
    InputCode();
}

void FileMenu::InputCode() const
{
    int code = SetCode();
    if (code == 1)
    {
        File file;
        file.SaveToFile();
        std::cout << NFile::SAVED << ". " << std::endl;
        InputCode();
    }
    else if (code == 2)
    {
        std::cout << NFile::ARE_YOU_SURE << std::endl;
        In yes;
        std::cin >> yes;
        if (std::string(yes) == "y")
        {
            File file;
            file.LoadFromFile();
            std::cout << NFile::LOADED << ". " << std::endl;
        }
        else
        {
            std::cout << NFile::NOT_LOADED << ". " << std::endl;
        }
        InputCode();
    }
    else if (code == 3)
    {
        std::shared_ptr<MainMenu> pMenu = std::make_shared<MainMenu>();
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

#pragma endregion
