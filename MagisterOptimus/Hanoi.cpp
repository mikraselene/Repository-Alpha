// 注释详见 AutoHanoi.cpp
#include <iostream>
using namespace std;
#define n 6
char layer[4][n + 1][2 * n + 2];
void initialize()
{
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
    for (int i = 1; i <= n; i++)
    {
        if (layer[a][i][n] + layer[a][i][n + 1] != 64)
        {
            for (int k = n; k >= 1; k--)
            {
                if (layer[b][k][n] + layer[b][k][n + 1] == 64)
                {
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
void display()
{
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
}
int main()
{

    initialize();
    int a, b;
    display();
    while (cin >> a >> b)
    {
        move_columns(a, b);
        system("clear");
        display();
    }
}
