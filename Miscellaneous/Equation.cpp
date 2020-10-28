#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;
int main()
{
    int x, y;     // x和y是行与列的符号
    int t, p, n;  // t是化三角形行列式的循环变量，p是求Dn的循环变量，n是阶数
    int f = 0;    // f的奇偶反映着行列式符号的变化
    double ratio; // 两行第一个元素的比值

    printf("Please input the number of unknowns:\nn = ");
    scanf("%d", &n);
    double a[n + 1][n + 1]; // 行列式的各项
    double c[n + 1];        // 次数为0的常数项
    double s[n + 1][n + 1]; // 储存行列式的各项
    double det[n + 1];      // D以及各Dn

    // 初始化D以及各Dn
    for (p = 0; p <= n; p++)
    {
        det[p] = 1;
    }

    printf("\nIf you want to solve the equation:");
    cout << endl
         << " -" << endl;
    printf("| A11*X1 + A12*X2 +...+ A1n*Xn = B1\n");
    printf("| A21*X1 + A22*X2 +...+ A2n*Xn = B2\n");
    printf("|    :   +    :   +...+    :   =  :\n");
    printf("| An1*X1 + An2*X2 +...+ Ann*Xn = Bn\n");
    cout << " -" << endl;
    printf("Please input values as follows:\n");
    printf("A11 A12 ... A1n B1\n");
    printf("A21 A22 ... A2n B2\n");
    printf(" :   :  ...  :   :\n");
    printf("An1 An2 ... Ann Bn\n\n");
    for (x = 1; x <= n; x++)
    {
        for (y = 1; y <= n; y++)
        {
            scanf("%lf", &a[x][y]);
            s[x][y] = a[x][y]; // 储存行列式的各项
        }
        scanf("%lf", &c[x]); // 读取次数为0的常数项
    }

    for (p = 0; p <= n; p++)
    {
        // 改D为Dn
        for (x = 1; x <= n; x++)
        {
            a[x][p] = c[x];
        }

        // 化为三角形行列式
        for (t = 1; t <= n; t++)
        {
            for (x = t + 1; x <= n; x++)
            {
                // 如果某对角线元素为0
                if (a[t][t] == 0)
                {
                    // 检查哪一行可以调换
                    for (int j = t + 1; j <= n; j++)
                    {
                        // 一旦发现可以调换的行
                        if (a[j][t] != 0)
                        {
                            f++; // 行列式值*-1
                            // 调换行
                            for (int i = t; i <= n; i++)
                            {
                                a[0][i] = a[j][i];
                                a[j][i] = a[t][i];
                                a[t][i] = a[0][i];
                                ratio = (a[x][t] / a[t][t]);
                            }
                            // 结束检查
                            break;
                        }
                        // 如果全是0
                        else
                        {
                            cout << "\n------------------------------";
                            cout << "------------------------------\n";
                            cout << endl;
                            cout << "不想算了，本质上还是一条懒狗\n\n";
                            // 我真不会写了
                            return 0;
                        }
                    }
                }
                else
                {
                    ratio = (a[x][t] / a[t][t]);
                }
                // 通过行相减来化为三角形行列式
                for (y = t; y <= n; y++)
                {
                    a[x][y] = a[x][y] - ratio * a[t][y];
                }
            }
        }

        // 求行列式
        for (x = 1; x <= n; x++)
        {
            det[p] = det[p] * a[x][x];
        }
        det[p] = pow(-1, f) * det[p];
        f = 0;

        // 恢复行列式的各项至刚赋值后的状态
        for (x = 1; x <= n; x++)
        {
            for (y = 1; y <= n; y++)
            {
                a[x][y] = s[x][y];
            }
        }
    }

    // 输出结果
    cout << "\n------------------------------------------------------------\n";
    cout << " -" << endl;
    for (p = 1; p <= n; p++)
    {
        cout << "| X" << p << " = " << det[p] / det[0] << endl; // Xn=Dn/D
    }
    cout << " -" << endl;
    return 0;
}
