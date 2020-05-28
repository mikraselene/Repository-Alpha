#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include "inc/date.h"
#include "inc/asset.h"
#include "inc/bill.h"
#include "inc/menu.h"
#include "inc/file.h"
#include "inc/category.h"
#include "inc/fitting.h"

using namespace std;

void Exit()
{
    //SAVE
    //DELETE
}

int main()
{
    extern vector<Bill *> pBill;
    File file;
    file.LoadFromFile();
    extern MainMenu *pMenu;
    pMenu->Menu();
}
