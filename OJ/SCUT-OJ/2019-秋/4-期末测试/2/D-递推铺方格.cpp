#include <iostream>
using namespace std;
int main()
{
    int n;
    while (cin >> n)
    {
        long long a[2000];
        a[0] = 0;
        a[1] = 1;
        a[2] = 2;
        for (int i = 3; i <= n; i++)
        {
            a[i] = a[i - 1] + a[i - 2];
        }
        cout << a[n] << endl;
    }
}
