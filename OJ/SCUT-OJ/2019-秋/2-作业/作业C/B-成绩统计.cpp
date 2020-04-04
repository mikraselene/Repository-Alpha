#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;
double ave(int s[], int n)
{
    double sum = 0;
    for (int i = 1; i <= n; i++)
    {
        sum += s[i];
    }
    return sum / n;
}
double aveMsd(int s[], int n)
{
    double dsum = 0;
    double a = ave(s, n);
    for (int i = 1; i <= n; i++)
    {
        dsum += pow((s[i] - a), 2);
    }
    return sqrt(dsum / n);
}
int main()
{
    int n;
    while (cin >> n)
    {
        int s[n + 1];
        for (int i = 1; i <= n; i++)
        {
            cin >> s[i];
        }
        cout << fixed << setprecision(1) << ave(s, n) << " " << aveMsd(s, n) << endl;
    }
}
