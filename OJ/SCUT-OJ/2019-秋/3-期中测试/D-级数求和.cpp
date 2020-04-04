#include <iomanip>
#include <iostream>
using namespace std;
int main()
{
    int n;
    double i;
    double s = 0;
    while (cin >> n)
    {
        double r;
        for (i = 1; i <= n; i++)
        {
            r = (2 * i - 1) / (2 * i + 1);
            s = s + r;
        }
        cout << setiosflags(ios::fixed) << setprecision(2) << s << endl;
        s = 0;
    }
}
