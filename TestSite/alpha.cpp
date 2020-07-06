#include <iostream>
#include <cmath>
using namespace std;

int Func1(int a)
{
    return !(a & (a - 1));
}

int Func2(int a)
{
    return log2(a) == int(log2(a));
}

int main()
{
}