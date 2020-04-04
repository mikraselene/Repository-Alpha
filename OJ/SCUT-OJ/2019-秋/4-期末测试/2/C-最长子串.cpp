#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
int main()
{
    char a[300];
    int n;
    while (cin >> n)
    {
        int cnt[26];
        bool flag[26];
        for (int i = 0; i < 26; i++)
        {
            cnt[i] = 0;
            flag[i] = 0;
        }
        cin >> a;
        int l = strlen(a);
        int max = 0;
        for (int i = 0; i < l; i++)
        {
            cnt[a[i] - 'a']++;
        }
        for (int i = 0; i < l; i++)
        {
            for (int j = i; j < l; j++)
            {
                for (int g = 0; g < 26; g++)
                {
                    flag[g] = 0;
                }
                for (int k = i; k <= j; k++)
                {
                    flag[a[k] - 'a'] = 1;
                }
                bool f = 0;
                for (int q = 0; q < 26; q++)
                {
                    if (cnt[q] < n && flag[q] == 1)
                    {
                        f = 1;
                        break;
                    }
                }
                if (f == 0 && max <= (j - i + 1))
                {
                    max = j - i + 1;
                }
            }
        }
        cout << max << endl;
    }
}
