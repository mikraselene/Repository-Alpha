#include <iostream>
using namespace std;
void ran(int a[], int b[], int n)
{
    int temp;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (a[j] < a[i])
            {
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
                temp = b[i];
                b[i] = b[j];
                b[j] = temp;
            }
        }
    }
}
int main()
{
    int n;
    while (cin >> n)
    {
        int a[n];
        int b[n];
        for (int i = 0; i < n; i++)
        {
            cin >> a[i];
            b[i] = i;
        }
        ran(a, b, n);
        for (int i = n - 1; i >= 0; i--)
        {
            cout << a[i] << " " << b[i] << endl;
        }
    }
}
