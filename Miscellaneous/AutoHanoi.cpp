#include <iostream>
#include <unistd.h>
#define n 6
#define speed 10
#define interval 0.0005
using namespace std;
char layer[4][n + 1][2 * n + 2];
void initialize()
{
    // 初始化所有层为空格
    for (int c = 1; c <= 3; c++)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= 2 * n + 1; j++)
            {
                layer[c][i][j] = 32;
            }
        }
    }
    // 初始化柱1的层
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n - i; j++)
        {
            layer[1][i][j] = 32;
        }
        for (int j = n - i + 1; j <= n + i - 1; j = j + 2)
        {
            layer[1][i][j] = 32;
            layer[1][i][j + 1] = i + 64;
        }
        for (int j = 2 * n + 1; j >= n + i + 1; j--)
        {
            layer[1][i][j] = 32;
        }
    }
}
void move_columns(int a, int b)
{
    // 从上至下寻找柱a的第一层
    for (int i = 1; i <= n; i++)
    {
        if (layer[a][i][n] + layer[a][i][n + 1] != 64)
        {
            // 从下至上寻找柱b的第一层
            for (int k = n; k >= 1; k--)
            {
                if (layer[b][k][n] + layer[b][k][n + 1] == 64)
                {
                    // 移动层
                    for (int j = 1; j <= 2 * n + 1; j++)
                    {
                        layer[b][k][j] = layer[a][i][j];
                        layer[a][i][j] = 32;
                    }
                    break;
                }
            }
            break;
        }
    }
}
void display(int begin)
{
    // 输出
    for (int i = 1; i <= n; i++)
    {
        for (int c = 1; c <= 3; c++)
        {
            for (int j = 1; j <= 2 * n + 1; j++)
            {
                cout << layer[c][i][j];
            }
            cout << "\t";
        }
        cout << endl;
    }
    for (int c = 1; c <= 3; c++)
    {
        cout << "|";
        for (int j = 2; j <= n; j++)
        {
            cout << "-";
        }
        cout << c;
        for (int j = 2; j <= n; j++)
        {
            cout << "-";
        }
        cout << "|\t";
    }
    cout << endl
         << endl;
    int end = time(0);
    int t = end - begin;
    cout << "Speed: " << speed << " t/s" << endl;
    int h = t / 3600;
    int m = (t % 3600) / 60;
    int s = (t % 3600) % 60;
    cout << "Time Cost: " << h << " h " << m << " m " << s << " s" << endl;
}
void auto_move(int w, int x, int y, int z, int begin)
{
    // 用递归自动求解
    if (w)
    {
        auto_move(w - 1, x, z, y, begin);
        move_columns(x, y);
        usleep(1000000 / speed);
        system("clear");
        display(begin);
        auto_move(w - 1, z, y, x, begin);
    }
}
int main()
{
    int begin = time(0);
    initialize();
    display(begin);
    auto_move(n, 1, 2, 3, begin);
}
