#include <iomanip>
#include <iostream>
using namespace std;
int main()
{
    int s[3][3] = {{300, 250, 150}, {200, 240, 200}, {280, 210, 180}};
    int p[3] = {3500, 3300, 3800};
    double sum;
    for (int i = 0; i < 3; i++)
    {
        sum = 0;
        for (int j = 0; j < 3; j++)
        {
            sum += s[i][j] * p[j];
        }
        cout << "第" << i + 1 << "百货公司的营业额:";
        cout << fixed << setprecision(6) << sum << endl;
    }
}
