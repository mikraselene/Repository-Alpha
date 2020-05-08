#include <iostream>
#include "../inc/asset.h"
#include "../inc/date.h"

class AssetSubMenu
{
public:
    void ShowSubMenu();
};

class TransactionMenu : public AssetSubMenu
{
public:
    void InputTransaction();
    void InputAmount();

private:
    void InputCategory();
    void InputDate();
    double amount;
    string category;
    Date date;
};