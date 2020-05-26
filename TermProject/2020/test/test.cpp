#include <iostream>
#include <vector>
#include <string>

#include "date.h"

using namespace std;

int main()
{
    int n;
    Date today;
    while (cin >> n)
    {
        cout << today + n << endl;
    }
    return 0;
}

#if 0
#include <iostream>
#include <numeric>
#include <iomanip>
#include <algorithm>
#include <vector>

using namespace std;
class Bill;
vector<Bill *> pBill;
class Bill
{
public:
    Bill(int type, double amount, string info, Date date)
    {
        this->type = type;
        this->amount = amount;
        this->info = info;
        this->date = date;
    }
    void Add()
    {
        pBill.push_back(this);
    }

private:
    int type;
    double amount;
    string info;
    Date date;
};

int main()
{
}
const string MONTHLY = "";
const string WEEKLY = "";
const string DAILY = "";

vector<Date *> dateList;
class Period
{
public:
    Period(int am, int code, Date s)
    {
        amount = am;
        periodCode = code;
        startDate = s;
        if (code == 1)
        {
            period = MONTHLY;
        }
        if (code == 2)
        {
            period = WEEKLY;
        }
        if (code == 3)
        {
            period = DAILY;
        }
    }
    ~Period()
    {
        cout << "hello" << endl;
    }
    int CalculateWeekly()
    {
        Date today;
        int p = (today - startDate) / 7;
        return amount * p;
    }
    int CalculateDaily()
    {
        Date today;
        int p = today - startDate;
        return amount * p;
    }
    int CalculateMonthly()
    {
        Date today;
        int y = today.GetYear();
        int m = today.GetMonth();
        int d = today.GetDay();
        d = 31;
        Date *pt = new Date;
        while (1)
        {
            int maxday[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
            if ((y % 4 == 0 && y % 400 == 0) || (y % 4 == 0 && y % 100 != 0))
            {
                maxday[2]++;
            }
            pt = new Date(y, m % 12 + 1, d);
            if (*pt >= startDate)
            {
                break;
            }
            if (pt->IsLegal() == 0)
            {
                pt = new Date(y, m % 12 + 1, maxday[m % 12 + 1]);
            }
            dateList.push_back(pt);
            m++;
            if (m % 12 == 0)
            {
                y++;
            }
            //delete pt;
        }
        return amount * dateList.size();
    }

private:
    int periodCode;
    string period;
    int per;
    int amount;
    Date startDate;
};

int main()
{
    Date today;

    cout << today;

    Year Y(2022);
    Month M(6);
    Day D(16);
    Date S(Y, M, D);
    Period K(2000, 3, S);
    cout << K.CalculateMonthly() << endl;

    for (auto it : dateList)
    {
        cout << it << endl;
        delete it;
    }
    cout << endl;
    delete &K;
    for (auto it : dateList)
    {
        cout << it << endl;
    }
}
#endif

/*

2020.5  
2020.4  
2020.3  
2020.2  
2020.1  
class K
{
public:
    K(const int &s)
    {
        data = s;
    }
    void Print() const
    {
        cout << data;
    }

private:
    int data;
};
int main()
{
    double per[] = {12, 30, 40, 53, 22, 52, 11, 40, 23};
    int k = sizeof(per) / 8;
    double p[k];
    double sum = accumulate(per, per + k, 0);
    double max = 0;
    for (int i = 0; i < k; i++)
    {
        if (max < per[i])
        {
            max = per[i];
        }
    }
    for (int i = 0; i < k; i++)
    {
        p[i] = per[i] / sum;
        cout
            << fixed << setprecision(2) << setw(5) << setiosflags(ios::right)
            << p[i] * 100 << "% ";
        cout << "[";
        for (int j = 0; j < p[i] * 30 / (max / sum); j++)
        {
            cout << "#";
        }
        cout << "]";
        cout << endl;
    }
}

*/