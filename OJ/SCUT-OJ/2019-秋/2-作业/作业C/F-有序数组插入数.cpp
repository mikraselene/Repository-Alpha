#include <algorithm>
#include <iostream>
using namespace std;

int main()
{
    int n;
    while (cin >> n)
    {
        int a[n + 1];
        for (int i = 0; i < n; i++)
        {
            cin >> a[i];
        }
        cin >> a[n];
        sort(a, a + n + 1);
        cout << a[0];
        for (int i = 1; i < n; i++)
        {
            cout << " " << a[i];
        }
        cout << endl;
    }
}
