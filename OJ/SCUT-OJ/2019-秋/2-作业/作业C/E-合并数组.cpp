#include <algorithm>
#include <iostream>
using namespace std;
int main()
{
    int m, n;
    while (cin >> m >> n)
    {
        int a[m];
        int b[n];
        int s[m + n];
        for (int i = 0; i < m; i++)
        {
            cin >> a[i];
            s[i] = a[i];
        }
        for (int i = 0; i < n; i++)
        {
            cin >> b[i];
            s[i + m] = b[i];
        }
        sort(s, s + (m + n));
        cout << s[0];
        for (int i = 1; i < m + n; i++)
        {
            cout << " " << s[i];
        }
        cout << endl;
    }
}
