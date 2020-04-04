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
        char a[100][100];
        int cnt = 0;
        for (int i = 0;; i++)
        {
            cin >> a[i];
            cnt++;
            if (getchar() == '\n')
                break;
        }
        cout << a[cnt - 1];
        for (int i = cnt - 2; i >= 0; i--)
        {
            cout << " " << a[i];
        }
        cout << endl;
    }
}
