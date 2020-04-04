// 摄氏温度转华氏温度
#include <iomanip>
#include <iostream>
using namespace std;
int main()
{
    double c;
    double f;
    while (cin >> c)
    {
        f = 9 * c / 5 + 32;
        cout << "F=" << fixed << setprecision(1) << f << endl;
    }
}
