#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
using namespace std;
int max(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (i == j || i == (n + 1 - j))
                {
                    cout << "X";
                }
                else
                {
                    cout << " ";
                }
                if (j == max(i, n + 1 - i))
                {
                    break;
                }
            }
            cout << endl;
        }
    }
}
