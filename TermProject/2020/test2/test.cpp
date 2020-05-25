#include <iostream>
#include <numeric>
#include <iomanip>
#include <algorithm>
using namespace std;
#include <iostream>
#include <iomanip>

using namespace std;

int a[2][12] = {{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
                {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};
int b[2] = {365, 366};
int judge(int a) //是否是闰年，是则返回1，不是则返回0
{
    if ((a % 4 == 0 && a % 100 != 0) || a % 400 == 0)
        return 1;
    else
        return 0;
}
//返回从1年1月1日开始（包括当天）到输入天数（不包括当天）所经历的天数
int days_1(int year, int month, int day)
{
    int sum = 0;
    for (int i = year; i > 1; i--)
    {
        sum += b[judge(i)];
    }
    for (int j = month; j > 1; j--)
    {
        sum += a[judge(year)][j - 1];
    }
    sum += day - 1;
    return sum;
}
//输入n（n大于0），则返回从1年1月1日（包括当天）开始经过了n天后的日期（不包括当天）
void days_2(int sum, int &year, int &month, int &day)
{
    for (year = 1; sum >= b[judge(year)]; year++)
    {
        sum -= b[judge(year)];
    }
    for (month = 0; sum >= a[judge(year)][month]; month++)
    {
        sum -= a[judge(year)][month];
    }
    month++;
    day = sum + 1;
    return;
}

int main()
{
    int year, month, day, n;
    while (cin >> year >> month >> day >> n)
    {
        n += days_1(year, month, day);
        days_2(n, year, month, day);
        cout << year << "." << month << "." << day << endl;
    }
    return 0;
}

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