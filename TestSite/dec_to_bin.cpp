#include <iostream>
using namespace std;
void bit(unsigned value)
{
    unsigned c;
    unsigned bitmask = 1 << 31;
    cout << bitmask << endl;
    cout << value << " = ";
    for (c = 1; c <= 32; c++)
    {
        cout << (value & bitmask ? "1" : "0");
        value <<= 1;
    }
    cout << endl;
}
int main()
{
    unsigned x;
    while (cin >> x)
    {
        bit(x);
    }
}
