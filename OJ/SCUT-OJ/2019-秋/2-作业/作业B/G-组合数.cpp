#include <iostream>
using namespace std;
int Multi(int m, int n)
{
    int mul = 1;
    for (int i = n; i <= m; i++)
    {
        mul *= i;
    }
    return mul;
}
int Fabricate(int m, int n)
{
    return Multi(m, m - n + 1) / Multi(n, 1);
}
int main()
{
    int m, n;
    while (cin >> m >> n)
        cout << Fabricate(m, n) << endl;
}
