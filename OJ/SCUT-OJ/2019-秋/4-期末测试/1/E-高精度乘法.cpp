#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
using namespace std;
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        char p[30];
        char q[30];
        int j[30] = {0};
        cin >> p;
        int l = strlen(p);
        int nump[10] = {0};
        int numq[10] = {0};
        char t[30];
        for (int i = 0; i < l; i++)
        {
            t[i] = p[l - 1 - i];
        }
        t[l] = '\0';
        j[0] = ((t[0] - '0') * 2) / 10;
        q[0] = ((t[0] - '0') * 2) % 10 + '0';
        for (int i = 1; i < l; i++)
        {
            j[i] = ((t[i] - '0') * 2) / 10;
            q[i] = ((t[i] - '0') * 2) % 10 + j[i - 1] + '0';
        }
        if (j[l - 1] != 0)
        {
            q[l] = '1';
            q[l + 1] = '\0';
        }
        else
        {
            q[l] = '\0';
        }

        for (int i = 0; q[i] != '\0'; i++)
        {
            numq[q[i] - '0']++;
        }
        for (int i = 0; t[i] != '\0'; i++)
        {
            nump[t[i] - '0']++;
        }
        bool flag = 0;
        for (int i = 0; i < 10; i++)
        {
            if (nump[i] != numq[i])
            {
                flag = 1;
                break;
            }
        }
        if (flag == 1)
        {
            cout << "No\n";
        }
        else
        {
            cout << "Yes\n";
        }
    }
}
