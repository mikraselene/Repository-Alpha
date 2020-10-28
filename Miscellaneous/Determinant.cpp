#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;
int main()
{
    int x, y;     // x和y是行与列的符号
    int t, n;     // t是化三角形行列式的循环变量，p是求Dn的循环变量，n是阶数
    int f = 0;    // f的奇偶反映着行列式符号的变化
    double ratio; // 两行第一个元素的比值
    while (1)
    {
        printf("Please input the order of A:\nn = ");
        scanf("%d", &n);
        double a[n + 1][n + 1];
        double s[n + 1][n + 1];
        double det = 1;

        for (x = 1; x <= n; x++)
        {
            for (y = 1; y <= n; y++)
            {
                scanf("%lf", &a[x][y]);
                s[x][y] = a[x][y]; // 储存行列式的各项
            }
        }

        // 化为三角形行列式
        for (t = 1; t <= n; t++)
        {
            for (x = t + 1; x <= n; x++)
            {
                // 如果某对角线元素为0则调换
                if (a[t][t] == 0)
                {
                    for (int j = t + 1; j <= n; j++)
                    {
                        if (a[j][t] != 0)
                        {
                            f++;
                            for (int i = t; i <= n; i++)
                            {
                                a[0][i] = a[j][i];
                                a[j][i] = a[t][i];
                                a[t][i] = a[0][i];
                                ratio = (a[x][t] / a[t][t]);
                            }
                            break;
                        }
                        else
                        {
                            det = 0;
                        }
                    }
                }
                else
                {
                    ratio = (a[x][t] / a[t][t]);
                }
                // 行相减
                for (y = t; y <= n; y++)
                {
                    a[x][y] = a[x][y] - ratio * a[t][y];
                }
            }
        }

        // 求行列式
        for (x = 1; x <= n; x++)
        {
            det = det * a[x][x];
        }
        det = pow(-1, f) * det;
        f = 0;

        // 恢复行列式的各项至刚赋值后的状态
        for (x = 1; x <= n; x++)
        {
            for (y = 1; y <= n; y++)
            {
                a[x][y] = s[x][y];
            }
        }

        cout << "det(A) = " << det << endl;
        cout << endl;
    }
}
