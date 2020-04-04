// 简单加密程序
#include <cmath>
#include <iostream>
using namespace std;
int main()
{
    int a[7], pswd[7], b[7];
    int n, i, n_one, n_two;
    while (cin >> n)
    {
        a[0] = 0;
        pswd[0] = 0;
        b[0] = 0;
        n_one = 0;
        n_two = 0;
        for (i = 1; i <= 6; i++)
        {
            a[i] = n / pow(10, 6 - i);
            n = n - a[i] * pow(10, 6 - i);
            pswd[i] = (a[i] + 7) % 10;
        }
        for (i = 6; i >= 1; i--)
        {
            n_one = n_one + pswd[i] * pow(10, i - 1);
            b[i] = ((pswd[i] + 3) % 10);
            n_two = n_two + b[i] * pow(10, 6 - i);
        }

        cout << "n1=" << n_one << " ";
        cout << "n2=" << n_two << endl;
    }
}
