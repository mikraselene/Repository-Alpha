#include "../inc/menu.h"

#define CLEAR system("clear")
//#define CLEAR system("cls")

using std::cerr;
using std::vector;

MainMenu *pMenu = new MainMenu;

void MainMenu::Menu()
{
    CLEAR;
    using namespace NMainMenu;
    cout << TITLE << endl;
    cout << "1. " << ASSET << endl
         << "2. " << BILL << endl
         << "3. " << WALLET << endl
         << "4. " << MFILE << endl
         << "5. " << HELP << endl
         << "6. " << EXIT << endl
         << END << endl;
    delete pMenu;
    InputCode();
}

void MainMenu::InputCode()
{
    int code = SetCode();
    if (code == 1)
    {
        pMenu = new AssetMenu;
        pMenu->Menu();
    }
    else if (code == 2)
    {
        pMenu = new BillMenu;
        pMenu->Menu();
    }
    else if (code == 3)
    {
        pMenu = new WalletMenu;
        pMenu->Menu();
    }
    else if (code == 4)
    {
        //pMenu = new FileMenu;
        //pMenu->Menu();
    }
    else if (code == 5)
    {
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
        - 新建 (4)
        - 编辑
        - 返回
    - 借贷
        - 新建 (2)
        - 编辑
        - 统计
        - 返回
    - 预算
        - 新建
        - 编辑
        - 返回
    - 返回

账单
    - 总览
        - 默认排序
        - 按时间排序
        - 按金额排序
        - 返回

    - 过滤
        - 按时间
        - 按金额
        - 按类别
        - 返回

    - 统计
    - 返回

钱包
    - 总览
    - 编辑
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
    delete pMenu;
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
        pMenu = new TransactionMenu;
        pMenu->Menu();
    }
    else if (code == 2)
    {
        pMenu = new DepositAndLoanMenu;
        pMenu->Menu();
    }
    else if (code == 3)
    {
        pMenu = new BudgetMenu;
        pMenu->Menu();
    }
    else if (code == 4)
    {
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
    delete pMenu;
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
        pMenu = new TransactionMenu;
        pMenu->Menu();
    }
    else if (code == 2)
    {
        Transaction *p = new Transaction;
        p->InputSingleTransaction(INCOME);
        pMenu = new TransactionMenu;
        pMenu->Menu();
    }
    else if (code == 3)
    {
        Transaction *p = new Transaction;
        p->InputRegularTransaction(EXPENSE);
        pMenu = new TransactionMenu;
        pMenu->Menu();
    }
    else if (code == 4)
    {
        Transaction *p = new Transaction;
        p->InputRegularTransaction(INCOME);
        pMenu = new TransactionMenu;
        pMenu->Menu();
    }
    else if (code == 5)
    {
        EditTransaction();
        pMenu = new TransactionMenu;
        pMenu->Menu();
    }
    else if (code == 6)
    {
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
    cout << AMOUNT << "\t\t"
         << CATEGORY << "\t\t"
         << DATE << "(" << START_DATE << ")\t\t"
         << PERIOD << endl;

    for (auto it : pTransaction)
    {
        it->Print();
    }
}

void TransactionMenu::EditTransaction()
{
    CLEAR;
    PrintAll();
    int code = SetCode();
}

void BudgetMenu::Menu()
{
    CLEAR;
    delete pMenu;
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
        pMenu = new BudgetMenu;
        pMenu->Menu();
    }
    else if (code == 2)
    {
        EditBudget();
        pMenu = new BudgetMenu;
        pMenu->Menu();
    }
    else if (code == 3)
    {
        GetStats();
        pMenu = new BudgetMenu;
        pMenu->Menu();
    }
    else if (code == 4)
    {
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
    delete pMenu;
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
        pMenu = new DepositAndLoanMenu;
        pMenu->Menu();
    }
    else if (code == 2)
    {
        DepositAndLoan *p = new DepositAndLoan;
        p->InputDepositAndLoan(LOAN);
        pMenu = new DepositAndLoanMenu;
        pMenu->Menu();
    }
    else if (code == 3)
    {
        EditDepositAndLoan();
        pMenu = new DepositAndLoanMenu;
        pMenu->Menu();
    }
    else if (code == 4)
    {
        GetStats();
        pMenu = new DepositAndLoanMenu;
        pMenu->Menu();
    }
    else if (code == 5)
    {
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
    extern vector<DepositAndLoan *> pDepoAndLoan;
    using namespace NDepositAndLoan;
    cout << PRINCIPLE << "\t\t"
         << INTEREST_RATE << "\t\t"
         << START_DATE << "\t\t"
         << END_DATE << "\t\t"
         << PERIOD << "\t\t"
         << INFO << endl;
    for (auto it : pDepoAndLoan)
    {
        it->Print();
    }
}

void DepositAndLoanMenu::EditDepositAndLoan()
{
    //TODO:
}
void DepositAndLoanMenu::GetStats()
{
    //TODO:
}

#pragma endregion

#pragma region "Bill"

void BillMenu::Menu()
{
    CLEAR;
    delete pMenu;
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
        pMenu = new BillMenu;
        pMenu->Menu();
    }
    else if (code == 2)
    {
        //TODO:
        //FILTER
        pMenu = new BillMenu;
        pMenu->Menu();
    }
    else if (code == 3)
    {
        //TODO:
        //STATISTICS
        pMenu = new BillMenu;
        pMenu->Menu();
    }
    else if (code == 4)
    {
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

void BillMenu::PrintAll()
{
}

#pragma endregion

#pragma region "Else"
extern Wallet *pWallet;
void WalletMenu::Menu()
{
    CLEAR;
    delete pMenu;
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
        pMenu = new WalletMenu();
        pMenu->Menu();
    }
    else if (code == 2)
    {
        pWallet->Withdraw();
        pMenu = new WalletMenu();
        pMenu->Menu();
    }
    else if (code == 3)
    {
        pWallet->Edit();
        pMenu = new WalletMenu();
        pMenu->Menu();
    }
    else if (code == 4)
    {
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

#pragma endregion
