#include <iostream>
#include <algorithm>
using namespace std;
#define X 5
#define Y 5
#define M 4
#define N 3

int Cutting(int n)
{
    if (n <= 3)
    {
        return n > 0 ? n - 1 : 0;
    }
    int *dp = new int[n + 1];
    for (int i = 0; i <= 3; i++)
    {
        dp[i] = i;
    }
    int max = 0;
    for (int i = 4; i <= n; i++)
    {
        max = 0;
        for (int j = 1; j <= i / 2; j++)
        {
            int val = dp[j] * dp[i - j];
            max = val > max ? val : max;
        }
        dp[i] = max;
    }
    max = dp[n];
    return max;
}

int Jump(int n)
{
    if (n <= 2)
    {
        return n > 0 ? n : 0;
    }
    int *dp = new int[n + 1];
    for (int i = 0; i <= 2; i++)
    {
        dp[i] = i;
    }
    for (int i = 3; i <= n; i++)
    {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    return dp[n];
}
int Paths(int m, int n)
{
    int **dp = new int *[m];
    for (int i = 0; i < m; i++)
    {
        dp[i] = new int[n];
    }
    dp[0][0] = 0;
    for (int i = 0; i < n; i++)
    {
        dp[0][i] = 1;
    }
    for (int i = 0; i < m; i++)
    {
        dp[i][0] = 1;
    }
    for (int i = 1; i < m; i++)
    {
        for (int j = 1; j < n; j++)
        {
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
        }
    }
    return dp[m - 1][n - 1];
}

int main()
{
    cout << Cutting(X) << endl;
    cout << Jump(Y) << endl;
    cout << Paths(M, N) << endl;
}