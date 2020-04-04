#include <algorithm>
#include <iostream>
using namespace std;
int main()
{
    int n;
    while (cin >> n)
    {
        int *p = new int[n];
        for (int i = 0; i < n; i++)
        {
            cin >> p[i];
        }
        for (int i = 0; i < n / 2; i++)
        {
            swap(p[i], p[n - 1 - i]);
        }
        cout << p[0];
        for (int i = 1; i < n; i++)
        {
            cout << " " << p[i];
        }
        cout << endl;
    }
}
