#include <iostream>
#include <unistd.h>
using namespace std;
#define height 30
#define width 40
#define max 100
int x, y;                                   // 世界的行数和列数
bool cell[height + 2][width + 2] = {0};     // 细胞们
bool new_cell[height + 2][width + 2] = {0}; // 用来更新的细胞们
void spawn()
{
    srand(time(0));
    for (x = 1; x <= height; x++)
    {
        for (y = 1; y <= width; y++)
        {
            // 随机决定初始细胞的状态
            new_cell[x][y] = rand() % 2;
        }
    }
}
void update()
{
    for (x = 1; x <= height; x++)
    {
        for (y = 1; y <= width; y++)
        {
            // 获取相邻细胞的存活数
            int count = 0;
            for (int i = x - 1; i <= x + 1; i++)
            {
                for (int j = y - 1; j <= y + 1; j++)
                {
                    if (((i != x) || (j != y)) && cell[i][j] == 1)
                    {
                        count++;
                    }
                }
            }
            // 用规则判断新细胞的状态
            if (count == 2)
            {
                new_cell[x][y] = cell[x][y];
            }
            else if (count == 3)
            {
                new_cell[x][y] = 1;
            }
            else
            {
                new_cell[x][y] = 0;
            }
        }
    }
}
void output(int k)
{
    cout << "step " << k << endl
         << endl;
    for (x = 1; x <= height; x++)
    {
        for (y = 1; y <= width; y++)
        {
            // 更新细胞并输出其状态
            cell[x][y] = new_cell[x][y];
            if (cell[x][y] == 1)
            {
                cout << "* ";
            }
            if (cell[x][y] == 0)
            {
                cout << "  ";
            }
        }
        cout << endl;
    }
    cout << endl;
    usleep(80000);
    if (k != max)
    {
        system("clear");
    }
}
int main()
{
    while (1)
    {
        spawn();
        for (int k = 1; k <= max; k++)
        {
            output(k);
            update();
        }
        // 结束条件
        if (getchar() == '\n')
        {
            system("clear");
        }
        else
        {
            return 0;
        }
    }
}
