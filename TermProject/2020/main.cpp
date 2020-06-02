#include <iostream>

#include "inc/date.h"
#include "inc/bill.h"
#include "inc/menu.h"
#include "inc/file.h"
#include "inc/category.h"

void Initialize()
{
    AddDefault();
    File file;
    file.LoadFromFile();
}

void Exit()
{
    File file;
    file.SaveToFile();

    extern std::vector<std::shared_ptr<Transaction>> pTransaction;
    extern std::vector<std::shared_ptr<DepositAndLoan>> pDepoAndLoan;
    extern std::vector<std::shared_ptr<Category>> pCategory;
    extern std::vector<std::shared_ptr<Bill>> pBill;
    extern std::vector<std::shared_ptr<Bill>> pFiltered;
    extern std::vector<std::shared_ptr<Category>> pCategory;
    pTransaction.clear();
    pDepoAndLoan.clear();
    pCategory.clear();
    pBill.clear();
    pFiltered.clear();
    pCategory.clear();
}

int main()
{
    Initialize();
    extern std::shared_ptr<MainMenu> pMenu;
    pMenu->Menu();
    Exit();
}
