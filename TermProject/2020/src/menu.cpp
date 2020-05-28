#include "../inc/menu.h"

using std::cerr;
using std::vector;

MainMenu *pMenu = new MainMenu;
string Division(int n)
{
    string s(n, '-');
    return s;
}
void MainMenu::Menu()
{
    CLEAR;
    Refresh();
    using namespace NMainMenu;
    cout << TITLE << endl;
    cout << "1. " << ASSET << endl
         << "2. " << BILL << endl
         << "3. " << WALLET << endl
         << "4. " << MFILE << endl
         << "5. " << HELP << endl
         << "6. " << EXIT << endl
         << END << endl;
    InputCode();
}

void MainMenu::InputCode()
{
    int code = SetCode();
    if (code == 1)
    {
        delete pMenu;
        pMenu = new AssetMenu;
        pMenu->Menu();
    }
    else if (code == 2)
    {
        delete pMenu;
        pMenu = new BillMenu;
        pMenu->Menu();
    }
    else if (code == 3)
    {
        delete pMenu;
        pMenu = new WalletMenu;
        pMenu->Menu();
    }
    else if (code == 4)
    {
        //delete pMenu;
        //pMenu = new FileMenu;
        //pMenu->Menu();
    }
    else if (code == 5)
    {
        //delete pMenu;
        //pMenu = new HelpMenu;
        //pMenu->Menu();
    }
    else if (code == 6)
    {
        return;
    }
    else
    {
        using namespace NError;
        cerr << ERR_ILLEGAL_NUMBER << ", "
             << PLEASE_INPUT_AGAIN << ". "
             << endl;
        InputCode();
    }
}
/*

财产
    - 收支
        - 新建 (4) ok
        - 编辑 TODO:
        - 返回 ok
    - 借贷
        - 新建 (2) ok TODO:
        - 编辑 TODO:
        - 统计 ?
        - 返回 
    - 预算
        - 新建
        - 编辑
        - 返回
    - 返回

账单
    - 总览 ok
        - 默认排序 ok
        - 按时间排序 ok
        - 按金额排序 ok
        - 返回 ok

    - 过滤
        - 按时间
        - 按金额
        - 返回

    - 统计 ok
    - 返回

钱包
    - 总览 ok
    - 编辑 ok
    - 返回

文件
    - 读入
    - 保存
    - 导出
    - 返回

帮助
    -返回

退出

*/

void AssetMenu::Menu()
{
    CLEAR;
    using namespace NAssetMenu;
    cout << TITLE << endl;
    cout << "1. " << TRANSACTION << endl
         << "2. " << DEPO_AND_LOAN << endl
         << "3. " << BUDGET << endl
         << "4. " << BACK << endl
         << END << endl;

    InputCode();
}

void AssetMenu::InputCode()
{
    int code = SetCode();
    if (code == 1)
    {
        delete pMenu;
        pMenu = new TransactionMenu;
        pMenu->Menu();
    }
    else if (code == 2)
    {
        delete pMenu;
        pMenu = new DepositAndLoanMenu;
        pMenu->Menu();
    }
    else if (code == 3)
    {
        delete pMenu;
        pMenu = new BudgetMenu;
        pMenu->Menu();
    }
    else if (code == 4)
    {
        delete pMenu;
        pMenu = new MainMenu;
        pMenu->Menu();
    }
    else
    {
        using namespace NError;
        cerr << ERR_ILLEGAL_NUMBER << ", "
             << PLEASE_INPUT_AGAIN << ". "
             << endl;
        InputCode();
    }
}

int MainMenu::SetCode()
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

#pragma region "Asset"

void AssetMenu::PrintAll()
{
}

void TransactionMenu::Menu()
{
    CLEAR;
    using namespace NTransactionMenu;
    cout << TITLE << endl
         << "1. " << ADD_SINGLE_EXPENSE << endl
         << "2. " << ADD_SINGLE_INCOME << endl
         << "3. " << ADD_REGULAR_EXPENSE << endl
         << "4. " << ADD_REGULAR_INCOME << endl
         << "5. " << EDIT << endl
         << "6. " << BACK << endl
         << END << endl;

    InputCode();
}

void TransactionMenu::InputCode()
{
    int code = SetCode();
    if (code == 1)
    {
        Transaction *p = new Transaction;
        p->InputSingleTransaction(EXPENSE);
        delete pMenu;
        pMenu = new TransactionMenu;
        pMenu->Menu();
    }
    else if (code == 2)
    {
        Transaction *p = new Transaction;
        p->InputSingleTransaction(INCOME);
        delete pMenu;
        pMenu = new TransactionMenu;
        pMenu->Menu();
    }
    else if (code == 3)
    {
        Transaction *p = new Transaction;
        p->InputRegularTransaction(EXPENSE);
        delete pMenu;
        pMenu = new TransactionMenu;
        pMenu->Menu();
    }
    else if (code == 4)
    {
        Transaction *p = new Transaction;
        p->InputRegularTransaction(INCOME);
        delete pMenu;
        pMenu = new TransactionMenu;
        pMenu->Menu();
    }
    else if (code == 5)
    {
        EditTransaction();
        delete pMenu;
        pMenu = new TransactionMenu;
        pMenu->Menu();
    }
    else if (code == 6)
    {
        delete pMenu;
        pMenu = new AssetMenu;
        pMenu->Menu();
    }
    else
    {
        using namespace NError;
        cerr << ERR_ILLEGAL_NUMBER << ", "
             << PLEASE_INPUT_AGAIN << ". "
             << endl;
        InputCode();
    }
}

void TransactionMenu::PrintAll()
{
    CLEAR;
    extern vector<Transaction *> pTransaction;
    using namespace NTransaction;
    cout << Division(95) << endl
         << ID << "\t"
         << setw(14) << AMOUNT << "\t\t"
         << TYPE << "\t\t"
         << CATEGORY << "\t\t"
         << DATE << "(" << START_DATE << ")\t\t"
         << PERIOD << endl
         << Division(95) << endl;

    for (int i = 0; i < pTransaction.size(); i++)
    {
        cout << i + 1 << "\t";
        pTransaction[i]->SetId(i + 1);
        pTransaction[i]->Print();
    }
    cout << Division(95) << endl;
}

void TransactionMenu::EditTransaction()
{
    CLEAR;
    PrintAll();
    using namespace NTransaction;
    cout << CHOOSE_A_TRANSACTION << ", " << PRESS_ENTER_TO_EXIT << ". " << endl;
    int code = SetCode();
    extern vector<Transaction *> pTransaction;
    if (code >= 1 && code <= pTransaction.size())
    {
        pTransaction[code - 1]->Submenu();
        EditTransaction();
    }
    else if (code == 0)
    {
        return;
    }
    else
    {
        using namespace NError;
        cerr << ERR_ILLEGAL_NUMBER << ", "
             << PLEASE_INPUT_AGAIN << ". "
             << endl;
        EditTransaction();
    }
}

void BudgetMenu::Menu()
{
    CLEAR;
    using namespace NBudgetMenu;
    cout << TITLE << endl
         << "1. " << ADD << endl
         << "2. " << EDIT << endl
         << "3. " << STATISTICS << endl
         << "4. " << BACK << endl
         << END << endl;
    InputCode();
    //Menu();
}

void BudgetMenu::InputCode()
{
    int code = SetCode();
    if (code == 1)
    {
        Budget *p = new Budget;
        p->InputBudget();
        delete pMenu;
        pMenu = new BudgetMenu;
        pMenu->Menu();
    }
    else if (code == 2)
    {
        EditBudget();
        delete pMenu;
        pMenu = new BudgetMenu;
        pMenu->Menu();
    }
    else if (code == 3)
    {
        GetStats();
        delete pMenu;
        pMenu = new BudgetMenu;
        pMenu->Menu();
    }
    else if (code == 4)
    {
        delete pMenu;
        pMenu = new AssetMenu;
        pMenu->Menu();
    }
    else
    {
        using namespace NError;
        cerr << ERR_ILLEGAL_NUMBER << ", "
             << PLEASE_INPUT_AGAIN << ". "
             << endl;
        InputCode();
    }
}

void BudgetMenu::PrintAll()
{
    CLEAR;
    extern vector<Budget *> pBudget;
    using namespace NBudget;
    cout << BUDGET << "\t\t"
         << CATEGORY << "\t\t"
         << START_DATE << endl;
    for (auto it : pBudget)
    {
        it->Print();
    }
}

void BudgetMenu::EditBudget()
{
    //TODO:
}
void BudgetMenu::GetStats()
{
    //TODO:
}

void DepositAndLoanMenu::Menu()
{
    CLEAR;
    using namespace NDepositAndLoanMenu;
    cout << TITLE << endl
         << "1. " << ADD_DEPOSIT << endl
         << "2. " << ADD_LOAN << endl
         << "3. " << EDIT << endl
         << "4. " << STATISTICS << endl
         << "5. " << BACK << endl
         << END << endl;
    InputCode();
    //Menu();
}

void DepositAndLoanMenu::InputCode()
{
    int code = SetCode();
    if (code == 1)
    {
        DepositAndLoan *p = new DepositAndLoan;
        p->InputDepositAndLoan(DEPOSIT);
        delete pMenu;
        pMenu = new DepositAndLoanMenu;
        pMenu->Menu();
    }
    else if (code == 2)
    {
        DepositAndLoan *p = new DepositAndLoan;
        p->InputDepositAndLoan(LOAN);
        delete pMenu;
        pMenu = new DepositAndLoanMenu;
        pMenu->Menu();
    }
    else if (code == 3)
    {
        EditDepositAndLoan();
        delete pMenu;
        pMenu = new DepositAndLoanMenu;
        pMenu->Menu();
    }
    else if (code == 4)
    {
        GetStats();
        delete pMenu;
        pMenu = new DepositAndLoanMenu;
        pMenu->Menu();
    }
    else if (code == 5)
    {
        delete pMenu;
        pMenu = new AssetMenu;
        pMenu->Menu();
    }
    else
    {
        using namespace NError;
        cerr << ERR_ILLEGAL_NUMBER << ", "
             << PLEASE_INPUT_AGAIN << ". "
             << endl;
        InputCode();
    }
}

void DepositAndLoanMenu::PrintAll()
{
    CLEAR;
    /*
    bool isCompound;
    double principle;
    double interest;
    double totalInterest;
    Date start;
    Period period;
    string info;
    int type;
    */
    extern vector<DepositAndLoan *> pDepoAndLoan;
    using namespace NDepositAndLoan;
    cout << Division(115) << endl
         << ID << "\t"
         << setw(14) << PRINCIPLE << "\t"
         << setw(14) << INTEREST_RATE << "*\t\t"
         << PERIOD << "\t\t"
         << TYPE << "\t\t"
         << START_DATE << "\t\t"
         << INFO << endl
         << Division(115) << endl;
    for (int i = 0; i < pDepoAndLoan.size(); i++)
    {
        cout << i + 1 << "\t";
        pDepoAndLoan[i]->Print();
    }
    cout << Division(115) << endl;
    cout << "* " << RATE_HELP << endl;
}

void DepositAndLoanMenu::EditDepositAndLoan()
{
    CLEAR;
    PrintAll();
    using namespace NDepositAndLoan;
    cout << CHOOSE_A_DEPOSIT_OR_LOAN << ", " << PRESS_ENTER_TO_EXIT << ". " << endl;
    int code = SetCode();
    extern vector<DepositAndLoan *> pDepoAndLoan;
    if (code >= 1 && code <= pDepoAndLoan.size())
    {
        //pDepoAndLoan[code - 1]->Edit();
        //TODO:
    }
    else if (code == 0)
    {
        return;
    }
    else
    {
        using namespace NError;
        cerr << ERR_ILLEGAL_NUMBER << ", "
             << PLEASE_INPUT_AGAIN << ". "
             << endl;
        EditDepositAndLoan();
    }
}
void DepositAndLoanMenu::GetStats()
{
    extern vector<DepositAndLoan *> pDepoAndLoan;
    for (auto it : pDepoAndLoan)
    {
        it->PrintTotalInterest();
    }
    getchar();
}

#pragma endregion

#pragma region "Bill"

void BillMenu::Menu()
{
    CLEAR;
    using namespace NBillMenu;
    cout << TITLE << endl;
    cout << "1. " << OVERVIEW << endl
         << "2. " << FILTER << endl
         << "3. " << STATISTICS << endl
         << "4. " << BACK << endl
         << END << endl;
    InputCode();
}
void BillMenu::InputCode()
{
    int code = SetCode();
    if (code == 1)
    {
        //TODO:
        //OVERVIEW
        delete pMenu;
        pMenu = new OverviewMenu;
        pMenu->Menu();
    }
    else if (code == 2)
    {
        //TODO:
        //FILTER
        delete pMenu;
        pMenu = new BillMenu;
        pMenu->Menu();
    }
    else if (code == 3)
    {
        //TODO:
        //STATISTICS
        delete pMenu;
        pMenu = new StatisticsMenu;
        pMenu->Menu();
    }
    else if (code == 4)
    {
        delete pMenu;
        pMenu = new MainMenu;
        pMenu->Menu();
    }
    else
    {
        using namespace NError;
        cerr << ERR_ILLEGAL_NUMBER << ", "
             << PLEASE_INPUT_AGAIN << ". "
             << endl;
        InputCode();
    }
}

void OverviewMenu::Menu()
{
    CLEAR;
    extern vector<Bill *> pBill;
    vector<Bill *> temp(pBill);

    using namespace NBillMenu;
    cout << OVERVIEW_TITLE << endl;
    cout << "1. " << BY_DATE << "(" << DESCEND << ")" << endl
         << "2. " << BY_DATE << "(" << ASCEND << ")" << endl
         << "3. " << BY_AMOUNT << "(" << DESCEND << ")" << endl
         << "4. " << BY_AMOUNT << "(" << ASCEND << ")" << endl
         << "5. " << BACK << endl
         << OVERVIEW_END << endl;

    InputCode();
}

void OverviewMenu::InputCode()
{
    int code = SetCode();
    if (code <= 4 && code >= 1)
    {
        delete pMenu;
        pMenu = new OverviewMenu;
        PrintAll(code);
        pMenu->Menu();
    }
    else if (code == 5)
    {
        delete pMenu;
        pMenu = new BillMenu;
        pMenu->Menu();
    }
    else
    {
        using namespace NError;
        cerr << ERR_ILLEGAL_NUMBER << ", "
             << PLEASE_INPUT_AGAIN << ". "
             << endl;
        InputCode();
    }
}

void OverviewMenu::PrintAll(int flag)
{
    CLEAR;
    extern vector<Bill *> pBill;
    vector<Bill *> temp(pBill);

    if (flag == 1)
    {
        sort(temp.begin(), temp.end(),
             [](Bill *A, Bill *B) { return A->GetDate() > B->GetDate(); });
    }
    else if (flag == 2)
    {
        sort(temp.begin(), temp.end(),
             [](Bill *A, Bill *B) { return A->GetDate() < B->GetDate(); });
    }
    else if (flag == 3)
    {
        sort(temp.begin(), temp.end(),
             [](Bill *A, Bill *B) { return A->GetAmount() > B->GetAmount(); });
    }
    else if (flag == 4)
    {
        sort(temp.begin(), temp.end(),
             [](Bill *A, Bill *B) { return A->GetAmount() < B->GetAmount(); });
    }
    using namespace NBill;

    cout << Division(90) << endl
         << setw(12) << AMOUNT << "\t"
         << TYPE << "\t\t\t"
         << DATE << "\t\t\t"
         << INFO << endl
         << Division(90) << endl;
    for (auto it : temp)
    {
        it->Print();
    }
    cout << Division(90) << endl
         << PRESS_ANY_KEY;
    getchar();
}

void StatisticsMenu::Menu()
{
    CLEAR;
    PrintStats();
}
void StatisticsMenu::PrintStats()
{
    extern vector<Bill *> pBill;
    sort(pBill.begin(), pBill.end(),
         [](Bill *A, Bill *B) { return A->GetDate() < B->GetDate(); });
    Date today;
    int currentYear = today.GetYear();
    int currentMonth = today.GetMonth();
    int firstYear = pBill[0]->GetDate().GetYear();
    int firstMonth = pBill[0]->GetDate().GetMonth();
    int totalMonth = (currentYear - firstYear) * 12 + (currentMonth - firstMonth);

    vector<BILL_BY_MONTH> y(totalMonth + 1, {0, 0, 0});

    int monthCount = 0;
    for (int i = 0; i < pBill.size(); i++)
    {
        if (pBill[i]->IsExpense())
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

    //LeastSquare ls(y);
    //ls.Fitting();
    //cout << ls.Y(a + 1) << endl;

    vector<double> monthAmount(totalMonth);

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

    using namespace std;

    monthAmount[totalMonth] = fit;

    for (int i = 0; i < totalMonth; i++)
    {
        cout << y[i].year << "."
             << setw(2) << setfill('0') << y[i].month << ", "
             << setfill(' ');

        cout << fixed << setprecision(2)
             << y[i].amount << NBill::YUAN << " ";
        cout << endl;
        cout << "[";
        for (int j = 0; j < monthAmount[i] * 30 / max; j++)
        {
            cout << "#";
        }
        cout << "]";
        cout << endl;
    }

    cout << currentYear << "."
         << setw(2) << setfill('0') << currentMonth << ", "
         << setfill(' ');

    cout << fixed << setprecision(2)
         << y[totalMonth].amount << NBill::YUAN << " ";
    //<< percent[i] * 100 << "% ";
    cout << endl;
    if (y[totalMonth].amount / fit < 1)
    {
        cout << "[";
        for (int j = 0; j < monthAmount[totalMonth] * 30 / max; j++)
        {
            if (j < (monthAmount[totalMonth] * 30 / max) * y[totalMonth].amount / fit)
            {
                cout << "#";
            }
            else
            {
                cout << " ";
            }
        }
        cout << "] ";
    }
    else
    {

        cout << "[";
        for (int j = 0;
             j < (monthAmount[totalMonth] * 30 / max) * y[totalMonth].amount / fit;
             j++)
        {
            if (j == int(monthAmount[totalMonth] * 30 / max))
            {
                cout << "]";
            }
            else
            {
                cout << "#";
            }
        }
    }
    cout << endl;
    cout << Division(50)
         << endl;
    using namespace NBill;
    cout << EXPECTED
         << fit << YUAN
         << ", " << USED << y[totalMonth].amount * 100 / fit << "%. " << endl;
    cout << PRESS_ANY_KEY;
    getchar();
    delete pMenu;
    pMenu = new BillMenu;
    pMenu->Menu();
}

#pragma endregion

#pragma region "Else"
extern Wallet *pWallet;
void WalletMenu::Menu()
{
    CLEAR;
    using namespace NWalletMenu;
    cout << TITLE << endl;
    cout << BALANCE << ": " << pWallet->GetBalance() << endl;
    if (pWallet->GetBalance() < 0)
    {
        cout << "[" << NEGATIVE_BALANCE_WARNING << "]" << endl;
    }
    cout << "1. " << TOP_UP << endl
         << "2. " << WITHDRAW << endl
         << "3. " << EDIT << endl
         << "4. " << BACK << endl
         << END << endl;
    InputCode();
}
void WalletMenu::InputCode()
{
    int code = SetCode();
    if (code == 1)
    {
        pWallet->TopUp();
        delete pMenu;
        pMenu = new WalletMenu();
        pMenu->Menu();
    }
    else if (code == 2)
    {
        pWallet->Withdraw();
        delete pMenu;
        pMenu = new WalletMenu();
        pMenu->Menu();
    }
    else if (code == 3)
    {
        pWallet->Edit();
        delete pMenu;
        pMenu = new WalletMenu();
        pMenu->Menu();
    }
    else if (code == 4)
    {
        delete pMenu;
        pMenu = new MainMenu;
        pMenu->Menu();
    }
    else
    {
        using namespace NError;
        cerr << ERR_ILLEGAL_NUMBER << ", "
             << PLEASE_INPUT_AGAIN << ". "
             << endl;
        InputCode();
    }
}

void HelpMenu::Menu()
{
}

#pragma endregion
