#include <algorithm>
#include <cmath>
#include <iostream>
using namespace std;
bool cmp(int x, int y)
{
    return (abs(x) > abs(y));
}
int main()
{
    int n;
    while (~scanf("%d", &n) && n)
    {
        int a[n];
        for (int i = 0; i < n; i++)
        {
            cin >> a[i];
        }
        sort(a, a + n, cmp);
        cout << a[0];
        for (int i = 1; i < n; i++)
        {
            cout << " " << a[i];
        }
        cout << endl;
    }
}
