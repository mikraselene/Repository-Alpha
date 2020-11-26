#include <iostream>
using namespace std;

int Hash(int *pt, int key, int n)
{
    if (pt[key] == 0)
        return key;
    else
        key++;
    if (key == n)
        key = 0;
    Hash(pt, key, n);
    return 0;
}

int main()
{
    int n, num, key, j = 0, k = 0;
    cin >> n;
    int *pt = new int[n];
    int *pr = new int[n];
    for (; k < n; k++)
        pt[k] = 0;
    while (cin >> num)
    {
        pr[j++] = num;
        if (cin.get() == '\n')
            break;
    }
    num = j;
    for (j = 0; j < num; j++)
    {
        key = pr[j] % n;
        key = Hash(pt, key, n);
        pt[key] = pr[j];
    }
    for (int i = 0; i < n; i++)
        if (pt[i] != 0)
            cout << i << " " << pt[i] << endl;
}
