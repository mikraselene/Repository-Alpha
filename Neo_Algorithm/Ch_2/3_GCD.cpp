#include <iostream>

int GCD(int p, int q)
{
    return q == 0 ? p : GCD(q, p % q);
}

int main()
{
    int p = 12;
    int q = 15;
    std::cout << GCD(p, q) << std::endl;
}