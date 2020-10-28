#include <iostream>

int FastPower(int base, int power)
{
    if (power == 0)
    {
        return 1;
    }
    return FastPower(base * base, power / 2) * (power % 2 ? base : 1);
}

int main()
{
    int base = 2;
    int power = 10;
    std::cout << FastPower(base, power) << std::endl;
}