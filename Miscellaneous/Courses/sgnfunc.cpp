#include <iostream>
using namespace std;
int sgn(double a)
{
    int d = (2 * (a > 0) - 1);
    return d * (a && d);
}
int main()
{
    for (int i = -10; i <= 10; i++)
    {
        cout << "sgn(" << i << ") = " << sgn(i) << endl;
    }
}
