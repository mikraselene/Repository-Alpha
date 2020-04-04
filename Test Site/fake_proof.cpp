#include <cmath>
#include <iostream>
using namespace std;
bool is_prime(int n)
{
    for (int i = 2; i <= sqrt(n); i++)
    {
        if (!(n % i))
            return 0;
    }
    return 1;
}
int main()
{
    int a, b;
    while (cin >> a >> b)
    {
        a += (a % 2);
        for (int i = a; i <= b; i = i + 2)
        {
            for (int j = i / 2; j >= 1; j--)
            {
                if (is_prime(j) && is_prime(i - j))
                {
                    cout << i << "=" << j << "+" << i - j << endl;
                    break;
                }
            }
        }
    }
}
