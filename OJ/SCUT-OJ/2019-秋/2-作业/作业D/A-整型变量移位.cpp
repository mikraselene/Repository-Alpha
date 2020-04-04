#include <iostream>
using namespace std;
void bitDisplay(unsigned value)
{
    unsigned c;
    unsigned bitmask = 1 << 31;
    cout << value << "=";
    for (c = 1; c <= 32; c++)
    {
        cout << (value & bitmask ? '1' : '0');
        value <<= 1;
        if (c % 8 == 0 && c != 32)
            cout << ' ';
    }
    cout << endl;
}

int main()
{
    unsigned x;
    while (cin >> x)
    {
        bitDisplay(x);
        x >>= 4;
        bitDisplay(x);
    }
}
