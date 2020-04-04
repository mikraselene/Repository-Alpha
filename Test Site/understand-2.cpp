#include <iostream>
using namespace std;
int main()
{
    int i = 42;
    const int &r = i;
    const int &r2 = r + 1 - 1;
    cout << r2 << endl;
    i = 1;
    cout << r2 << endl;

    const int yjsp = 114514;
    const int &kmr = yjsp;
}
