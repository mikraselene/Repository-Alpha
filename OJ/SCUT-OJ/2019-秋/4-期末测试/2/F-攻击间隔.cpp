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
        int t;
        cin >> t;
        int sum = 0;
        sum = t;
        for (int i = 1; i < n; i++)
        {
            if (t + p[i - 1] >= p[i])
            {
                sum += (p[i] - p[i - 1]);
            }
            else
            {
                sum += t;
            }
        }
        cout << sum << endl;
    }
}
