#include <cmath>
#include <iostream>
using namespace std;
bool IsPrime(long long n)
{
    for (long long i = 2; i <= sqrt(n); i++)
    {
        if (n % i == 0)
        {
            return 0;
        }
    }
    return 1;
}
int main()
{
    long long n;
    while (cin >> n)
    {
        cout << IsPrime(n) << endl;
    }
}
