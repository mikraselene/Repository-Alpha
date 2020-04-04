#include <iostream>
#include <string.h>
using namespace std;
int main()
{
    char a[2000], b[2000];
    int c[2000];
    int n;
    cin >> n;
    for (int m = 1; m <= n; m++)
    {
        cin >> a >> b;
        int i, j, k = 0;
        int r = 0;
        int alen = strlen(a);
        int blen = strlen(b);
        for (i = alen - 1, j = blen - 1; i >= 0 && j >= 0; i--, j--)
        {
            int p = (a[i] - '0') + (b[j] - '0') + r;
            r = p / 10;
            c[k++] = p % 10;
        }

        while (i >= 0)
        {
            int p = (a[i] - '0') + r;
            r = p / 10;
            c[k++] = p % 10;
            i--;
        }
        while (j >= 0)
        {
            int p = (b[j] - '0') + r;
            r = p / 10;
            c[k++] = p % 10;
            j--;
        }
        if (r)
        {
            c[k++] = r;
        }
        cout << "Case " << m << ":" << endl;
        for (int i = 0; i <= alen - 1; i++)
        {
            cout << a[i];
        }
        cout << " + ";
        for (int i = 0; i <= blen - 1; i++)
        {
            cout << b[i];
        }
        cout << " = ";
        for (int i = k - 1; i >= 0; i--)
        {
            cout << c[i];
        }
        cout << endl;
        if (m != n)
        {
            cout << endl;
        }
    }
}
