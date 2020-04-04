// 求解最小值
#include <iostream>
using namespace std;
int main()
{
    int a, b, c, d, minab, mincd;
    while (cin >> a >> b >> c >> d)
    {
        if (b > a)
        {
            minab = a;
        }
        else
        {
            minab = b;
        }
        if (c > d)
        {
            mincd = d;
        }
        else
        {
            mincd = c;
        }
        if (mincd > minab)
        {
            cout << minab << endl;
        }
        else
        {
            cout << mincd << endl;
        }
    }
}
