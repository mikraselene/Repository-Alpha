#include <iostream>
#include "../inc/asset.h"
#include "../inc/date.h"

class AssetSubMenu
{
public:
    void SubMenu();
};

class TransactionMenu : public AssetSubMenu
{
public:
    void InputSingleTransaction();
    void InputRegularTransaction();
    void PrintAllSingle();
    void PrintAllRegular();

private:
    void InputAmount();
    void InputCategory();
    void InputDate();
    void InputPeriod();
    template <typename T1, typename T2, typename T3>
    void Print(T1, T2, T3);
    double amount;
    string category;
    Date date;
};