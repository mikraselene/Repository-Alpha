// 利用迭代公式求解输入正整数n的平方根
#include <cmath>
#include <iostream>
using namespace std;
int main()
{
    int n;
    double eps = 1e-8, sqrtn;
    while (cin >> n)
    {
        sqrtn = n;
        while (sqrtn - sqrt(n) >= eps || sqrtn - sqrt(n) <= -eps)
        {
            sqrtn = (sqrtn + n / sqrtn) / 2;
        }
        cout << sqrtn << endl;
    }
}
