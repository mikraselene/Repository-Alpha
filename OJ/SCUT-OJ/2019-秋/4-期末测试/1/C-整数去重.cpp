#include <algorithm>
#include <cmath>
#include <cstring>
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
        for (int i = 0; i < n; i++)
        {
            bool flag = 1;
            for (int j = 0; j < i; j++)
            {
                if (p[j] == p[i])
                    flag = 0;
            }
            if (flag)
            {
                cout << p[i] << " ";
            }
        }
        cout << endl;
    }
}
