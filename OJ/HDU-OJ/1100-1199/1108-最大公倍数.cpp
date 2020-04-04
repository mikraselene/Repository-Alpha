#include <iostream>
using namespace std;
#define LL long long
int gcd(LL a, LL b)
{
    return b ? gcd(b, a % b) : a;
}
int lcm(LL a, LL b)
{
    return a / gcd(a, b) * b;
}
int main()
{
    LL a = 0;
    LL b = 0;
    while (cin >> a >> b)
    {
        cout << lcm(a, b) << endl;
    }
}