#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

bool cmp(string str1, string str2)
{
    return str1.length() != str2.length()
               ? str1.length() < str2.length()
               : str1 < str2;
}

int main()
{
    string a;
    while (cin >> a)
    {
        string b[114514];
        int i = 0;
        int m = 0;
        int p = 0;
        bool flag1 = 0;
        bool flag2 = 0;
        a += '5';
        while (a[i] == '5')
        {
            i++;
        }
        for (; i < a.length(); i++)
        {
            if (a[i] == '5')
            {
                if (i + 1 > a.length())
                {
                    break;
                }
                if (a[i + 1] != '5')
                {
                    flag1 = 0;
                    flag2 = 0;
                    m++;
                }
                continue;
            }
            if (a[i] != '0')
            {
                flag1 = 1;
            }
            if (a[i] == '0' && !flag1)
            {
                b[m] = "0";
            }
            if (!flag2 && flag1)
            {
                b[m].erase(b[m].begin(), b[m].end());
            }
            if (flag1)
            {
                b[m] += a[i];
                flag2 = 1;
            }
        }
        sort(b, b + m, cmp);
        for (i = 0; i < m - 1; i++)
        {
            cout << b[i] << " ";
        }
        cout << b[i] << endl;
    }
    return 0;
}