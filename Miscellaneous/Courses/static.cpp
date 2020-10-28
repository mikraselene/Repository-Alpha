#include <iostream>
using namespace std;
int func()
{
    int a = 0;
    static int b = 1;
    a++;
    b++;
    cout << "a = " << a << "; b = " << b << endl;
    return a + b;
}
int main()
{
    for (int i = 1; i <= 10; i++)
    {
        cout << i << endl;
        cout << func() << endl;
    }
}
