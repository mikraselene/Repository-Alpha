#include <iostream>
#include <string>
#include "inc/date.h"
#include "inc/asset.h"
#include "inc/bill.h"
#include "inc/submenu.h"
#include "inc/category.h"

using namespace std;

template <typename T>
bool func(T A, T B)
{
    return A == B;
}

int main()
{
    extern list<Category *> pCategory;
    Category *p = new Category("hello");
    Category *q = new Category("world");
    p->Add();
    q->Add();
    TransactionMenu tMenu;
    for (int i = 0; i < 2; i++)
    {
        tMenu.InputSingleTransaction();
    }
    tMenu.PrintAllSingle();
}
