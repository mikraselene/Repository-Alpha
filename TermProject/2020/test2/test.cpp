/*------------
#include <iostream>
#include <algorithm>
#include <cmath>
#include <list>
#include <string>
#include "date.h"
using namespace std;

const string illegal_operation = "不合法的运算";
const string illegal_number = "不合法的数字";
const string negative_number = "输入不能为负数";
const string max_month = "不合法的月份";
const string max_day = "不合法的日期";

int ToInt(string in)
{
    for (int i = 0; i < in.size(); i++)
    {
        if (isdigit(in[i]) == 0)
        {
            throw illegal_number;
        }
    }
    int ans = 0;
    int p = 0;
    for (int i = in.size() - 1; i >= 0; i--)
    {
        ans += (in[i] - '0') * pow(10, p);
        p++;
    }
    return ans;
}

Date InputDate(string in)
{
    auto first = in.find(".");
    auto second = in.find_last_of(".");
    auto third = in.size();

    string yearstr = in.substr(0, first);
    string monthstr = in.substr(first + 1, second - first - 1);
    string daystr = in.substr(second + 1, third - second - 1);

    int maxday[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int year = ToInt(yearstr);
    int month = ToInt(monthstr);
    int day = ToInt(daystr);

    if ((year % 4 == 0 && year % 400 == 0) || (year % 4 == 0 && year % 100 != 0))
    {
        maxday[2]++;
    }
    if (month && month > 12)
    {
        throw max_month;
    }
    if (day && day > maxday[month])
    {
        throw max_day;
    }

    Year Y(year);
    Month M(month);
    Day D(day);
    Date x(Y, M, D);

    return x;
}

int main()
{
    while (1)
    {
        try
        {
            string a;
            getline(cin, a);
            InputDate(a).Print();
        }
        catch (const string msg)
        {
            cerr << msg << endl;
        }
    }
}

    AssetSubMenu();
  
    //rg.Add();
    //rg.Del();

    
    DepositAndLoan dp;
    DepositAndLoan dp2;
    dp.Add();
    dp2.Add();
    for (auto it = pDepoAndLoan.begin(); it != pDepoAndLoan.end(); it++)
    {
        (*it)->Print();
    }

    Test("hello");
    Test("i", 7);
    uint year = 2020;
    uint month = 1;
    uint day = 2;
    Year y(2020);
    Month m(1);
    Day x(1);
    Date D(y, m, x);
    Date da;
    D.Print();
    da.Print();

    
    extern list<Bill *> pFiltered;

    Bill b[10];
    Date today;
    for (int i = 0; i < 10; i++)
    {
        Bill *p = new Bill;
        p->Add(10 * i + 100, today, "z");
    }
    FLTR_AMOUNT param = {100, 150};
    Filter f(param);
    f.FilterByAmount();
    for (auto it = pFiltered.begin(); it != pFiltered.end(); it++)
    {
        (*it)->Print();
    }
    */

#include <iostream>
using namespace std;
int main()
{
    string alpha = "gulugulu";
    cout << alpha.length();
}