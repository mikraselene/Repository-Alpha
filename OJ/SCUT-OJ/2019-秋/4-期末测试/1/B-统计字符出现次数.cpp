#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
using namespace std;
bool is_prime(int n)
{
    for (int i = 2; i <= sqrt(n); i++)
    {
        if (!(n % i))
        {
            return 0;
        }
    }
    return 1;
}
int main()
{
    char p[200];
    while (cin >> p)
    {
        int a[27] = {0};
        for (int i = 0; p[i] != '\0'; i++)
        {
            a[p[i] - 'a' + 1]++;
        }
        int max = 1;
        int min = 1;
        for (int i = 1; i <= 26; i++)
        {
            if (a[i] >= max)
            {
                max = a[i];
            }
            else if (a[i] && a[i] <= min)
            {
                min = a[i];
            }
        }
        if (is_prime(max - min) && (max - min) && (max - min) != 1)
        {
            cout << "Lucky Word\n"
                 << max - min << endl;
        }
        else
        {
            cout << "No Answer\n"
                 << 0 << endl;
        }
    }
}
