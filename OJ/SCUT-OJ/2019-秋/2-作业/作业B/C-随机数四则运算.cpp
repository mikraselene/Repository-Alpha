#include <cmath>
#include <iostream>
using namespace std;
int R(int m, int n, bool flag)
{
    static int random = 0;
    do
    {
        random = (25173 * random + 13849) % 65536;
    } while (random < m || random >= n);
    if (flag == 0)
    {
        random = 0;
    }
    return random;
}
int main()
{
    int num, n, a, b;
    while (cin >> num >> n)
    {
        for (int i = 1; i <= n; i++)
        {
            a = R(pow(10, num - 1), pow(10, num), 1);
            b = R(pow(10, num - 1), pow(10, num), 1);
            cout << a << "+" << b << "=" << a + b << ", ";
            cout << a << "-" << b << "=" << a - b << ", ";
            cout << a << "*" << b << "=" << a * b << ", ";
            cout << a << "/" << b << "=" << a / b << endl;
        }
        R(1, 9, 0);
    }
}
