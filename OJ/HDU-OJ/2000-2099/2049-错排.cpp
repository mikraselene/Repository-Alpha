#include <iostream>
using namespace std;
#define LL long long
int main()
{
    int T;
    int n;
    int m;
    LL factorial[30] = {0};
    LL D[30] = {0};
    factorial[0] = 1;
    factorial[1] = 1;
    factorial[2] = 2;
    for (int i = 3; i < 30; i++)
    {
        factorial[i] = factorial[i - 1] * i;
    }
    D[0] = 0;
    D[1] = 1;
    D[2] = 1;
    D[3] = 2;
    for (int i = 4; i < 30; i++)
    {
        D[i] = (i - 1) * (D[i - 1] + D[i - 2]);
    }
    cin >> T;
    while (T--)
    {
        cin >> n >> m;
        LL C = factorial[n] / factorial[m] / factorial[n - m];
        cout << C * D[m] << endl;
    }
}
