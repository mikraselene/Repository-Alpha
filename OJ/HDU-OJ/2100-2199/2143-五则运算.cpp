#include <iostream>
using namespace std;
#define ll long long
int main()
{
    ll a, b, c;
    while (~scanf("%lld%lld%lld", &a, &b, &c))
    {
        int flag = 0;
        if (a + b == c || a + c == b || b + c == a)
            flag = 1;
        if (a * b == c || a * c == b || b * c == a)
            flag = 1;
        if ((b != 0 && (a % b == c || c % b == a)) || (c != 0 && (b % c == a || a % c == b)) ||
            (a != 0 && (c % a == b || b % a == c)))
            flag = 1;
        if (flag)
        {
            printf("oh,lucky!\n");
        }
        else
        {
            printf("what a pity!\n");
        }
    }
}
