#include <cmath>
#include <iostream>
#include <iomanip>
using namespace std;
const double Pi = 3.14159265358979;
int main()
{
    int n = 0;
    while (cin >> n)
    {
        cout << fixed << setprecision(5) << left;
        for (int i = 1; i <= n; i++)
        {
            double a = i * Pi / 180.0;
            cout << setw(3) << i
                 << setw(10) << sin(a) << setw(10) << cos(a) << tan(a) << endl;
        }
    }
}