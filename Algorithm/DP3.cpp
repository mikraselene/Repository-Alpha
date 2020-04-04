#include <iostream>
#include <algorithm>
using namespace std;

int p[11] = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
int t[11] = {0};

int CutRod(int n)
{
    for (int i = 1; i <= n; i++)
    {
        int max = 0;
        for (int j = 1; j <= i; j++)
        {
            if (p[j] + t[i - j] >= max)
            {
                max = p[j] + t[i - j];
            }
        }
        t[i] = max;
    }
    return t[n];
}

int main()
{
    int n = 0;
    while (cin >> n)
    {
        cout << CutRod(n) << endl;
    }
}