#include <algorithm>
#include <iostream>
using namespace std;
int main()
{
    int m, n;
    while (cin >> m >> n)
    {
        int *a = new int[m];
        int *b = new int[n];
        for (int i = 0; i < m; i++)
        {
            cin >> a[i];
        }
        for (int i = 0; i < n; i++)
        {
            cin >> b[i];
        }
        sort(a, a + m);
        sort(b, b + n);
        bool flag = 0;
        if (m < n)
        {
            for (int i = 0; i < m; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    if (a[i] == b[j])
                    {

                        if (flag)
                            cout << " ";
                        cout << b[j];
                        flag = 1;
                        a[i] = -114514;
                        b[j] = -1919810;
                        break;
                    }
                }
            }
        }
        else
        {
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < m; j++)
                {
                    if (a[j] == b[i])
                    {

                        if (flag)
                            cout << " ";
                        cout << b[i];
                        flag = 1;
                        a[j] = -114514;
                        b[i] = -1919810;
                        break;
                    }
                }
            }
        }
        cout << endl;
    }
}
