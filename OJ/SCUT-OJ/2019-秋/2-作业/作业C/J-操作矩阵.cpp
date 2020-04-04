#include <iostream>
using namespace std;
void input_m(int mat[1000][1000], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> mat[i][j];
        }
    }
}
void display(int mat[1000][1000], int n)
{
    for (int i = 1; i < n - 1; i++)
    {
        for (int j = 1; j < n - 1; j++)
        {
            if (j == 1)
            {
                cout << mat[i][j];
            }
            else
            {
                cout << " " << mat[i][j];
            }
        }
        cout << endl;
    }
}
int sum(int mat[1000][1000], int n)
{
    int s = 0;
    for (int i = 0; i < n; i++)
    {
        s += mat[i][i];
    }
    return s;
}
int main()
{
    int n;
    while (cin >> n)
    {
        int mat[1000][1000] = {0};
        input_m(mat, n);
        display(mat, n);
        cout << sum(mat, n) << endl;
    }
}
