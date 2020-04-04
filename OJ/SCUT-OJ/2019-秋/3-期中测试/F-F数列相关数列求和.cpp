#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;
int main()
{
    int n;
    double F[1000];
    while (cin >> n)
    {
        double s = 0;
        F[0] = 1;
        F[1] = 1;
        for (int i = 2; i <= n + 1; i++)
        {
            F[i] = F[i - 1] + F[i - 2];
        }
        for (int i = 1; i <= n; i++)
        {
            s = s - pow(-1, i) * F[i + 1] / F[i];
        }
        cout << setiosflags(ios::fixed) << setprecision(4) << s << endl;
    }
}
