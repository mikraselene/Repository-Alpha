#include <iomanip>
#include <iostream>
using namespace std;
double polya(double x, double n)
{
    if (n == 0)
    {
        return 1.0;
    }
    else if (n == 1)
    {
        return x;
    }
    else if (n > 1)
    {
        return ((2 * n - 1) * polya(x, n - 1) - (n - 1) * polya(x, n - 2)) / n;
    }
    else
    {
        return -1;
    }
}
int main()
{
    double x, n;
    while (cin >> x >> n)
    {
        cout << fixed << setprecision(4) << polya(x, n) << endl;
    }
}
