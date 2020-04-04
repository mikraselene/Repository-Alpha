#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
using namespace std;
int main()
{
    int n;
    while (cin >> n && n)
    {
        int m = n;
        string colour[n];
        int count[n];
        while (n--)
        {
            cin >> colour[n];
        }

        for (int i = 0; i <= m - 1; i++)
        {
            count[i] = 0;
            for (int j = m - 1; j >= 0; j--)
            {
                if (colour[i] == colour[j])
                {
                    count[i]++;
                }
            }
        }
        int max = 0;
        for (int i = 0; i < m; i++)
        {
            if (count[i] >= count[max])
            {
                max = i;
            }
        }
        cout << colour[max] << endl;
    }
}
