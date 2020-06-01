#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include "inc/date.h"
#include "inc/bill.h"
#include "inc/menu.h"
#include "inc/file.h"
#include "inc/category.h"
#include "inc/fitting.h"

int main()
{
    extern std::vector<std::shared_ptr<Bill>> pBill;
    File file;
    file.LoadFromFile();
    extern std::shared_ptr<MainMenu> pMenu;
    pMenu->Menu();
    file.SaveToFile();
}
