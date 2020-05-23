#include "../inc/menu.h"

#define CLEAR system("clear")
//#define CLEAR system("cls")

using std::cerr;
using std::vector;

MainMenu *pMenu = new MainMenu;

void MainMenu::Menu()
{
    delete pMenu;
    pMenu = new AssetMenu;
    pMenu->Menu();
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
    delete pMenu;
    using namespace NAssetMenu;
    cout << TITLE << endl;
    cout << "1. " << TRANSACTION << endl
         << "2. " << DEPO_AND_LOAN << endl
         << "3. " << BUDGET << endl
         << "4. " << BACK << endl
         << END << endl;
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
        pMenu = new AssetMenu;
        Menu();
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
    using namespace NTransactionMenu;
    cout << TITLE << endl
         << "1. " << ADD_SINGLE_EXPENSE << endl
         << "2. " << ADD_SINGLE_INCOME << endl
         << "3. " << ADD_REGULAR_EXPENSE << endl
         << "4. " << ADD_REGULAR_INCOME << endl
         << "5. " << EDIT << endl
         << "6. " << BACK << endl
         << END << endl;
    int code = SetCode();
    if (code == 1)
    {
        Transaction *p = new Transaction;
        p->InputSingleTransaction(EXPENSE);
    }
    else if (code == 2)
    {
        Transaction *p = new Transaction;
        p->InputSingleTransaction(INCOME);
    }
    else if (code == 3)
    {
        Transaction *p = new Transaction;
        p->InputRegularTransaction(EXPENSE);
    }
    else if (code == 4)
    {
        Transaction *p = new Transaction;
        p->InputRegularTransaction(INCOME);
    }
    else if (code == 5)
    {
        EditTransaction();
    }
    else if (code == 6)
    {
        AssetMenu::Menu();
    }
    else
    {
        Menu();
    }
}

void TransactionMenu::PrintAll()
{
    extern vector<Transaction *> pTransaction;
    using namespace NTransaction;
    cout << AMOUNT << "\t\t"
         << CATEGORY << "\t\t"
         << DATE << "\t\t"
         << endl;
    for (auto it : pTransaction)
    {
        it->Print();
    }
}

void TransactionMenu::EditTransaction()
{
    //TODO:
}

void BudgetMenu::Menu()
{
    using namespace NBudgetMenu;
    cout << TITLE << endl
         << "1. " << ADD << endl
         << "2. " << EDIT << endl
         << "3. " << STATISTICS << endl
         << "4. " << BACK << endl
         << END << endl;
    int code = SetCode();
    if (code == 1)
    {
        Budget *p = new Budget;
        //TODO:
    }
    else if (code == 2)
    {
        EditBudget();
    }
    else if (code == 3)
    {
        GetStats();
    }
    else if (code == 4)
    {
        AssetMenu::Menu();
    }
    else
    {
        Menu();
    }
}

void BudgetMenu::PrintAll()
{
    extern vector<Budget *> pBudget;
    using namespace NBudget;
    cout << BUDGET << "\t\t"
         << CATEGORY << "\t\t"
         << START_DATE << "\t\t"
         << endl;
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
    using namespace NDepositAndLoanMenu;
    cout << TITLE << endl
         << "1. " << ADD_DEPOSIT << endl
         << "2. " << ADD_LOAN << endl
         << "3. " << EDIT << endl
         << "4. " << STATISTICS << endl
         << "5. " << BACK << endl
         << END << endl;
    int code = SetCode();
    if (code == 1)
    {
        DepositAndLoan *p = new DepositAndLoan;
        //TODO:
    }
    else if (code == 2)
    {
        DepositAndLoan *p = new DepositAndLoan;
        //TODO:
    }
    else if (code == 3)
    {
        EditDepositAndLoan();
    }
    else if (code == 4)
    {
        GetStats();
    }
    else if (code == 5)
    {
        AssetMenu::Menu();
    }
    else
    {
        Menu();
    }
}

void DepositAndLoanMenu::PrintAll()
{
    extern vector<DepositAndLoan *> pDepoAndLoan;
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

#pragma endregion

#pragma region "Else"

#pragma endregion
