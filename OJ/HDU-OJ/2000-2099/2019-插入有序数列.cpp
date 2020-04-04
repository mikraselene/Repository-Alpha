#include <algorithm>
#include <iostream>
using namespace std;
int main()
{
    int n, x;
    while (~scanf("%d%d", &n, &x) && (n || x))
    {
        int a[n + 1];
        a[n] = x;
        for (int i = 0; i < n; i++)
        {
            cin >> a[i];
        }
        sort(a, a + n + 1);
        cout << a[0];
        for (int i = 1; i < n + 1; i++)
        {
            cout << " " << a[i];
        }
        cout << endl;
    }
}
