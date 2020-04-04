#include <iomanip>
#include <iostream>
using namespace std;
#define ll long long
int main()
{
    ll a;
    ll b;
    while (cin >> hex >> a >> b)
    {
        if (a + b >= 0)
            cout << setiosflags(ios::uppercase) << hex << a + b << endl;
        else
            cout << "-" << setiosflags(ios::uppercase) << hex << -a - b << endl;
    }
}
