#include <cmath>
#include <iostream>
using namespace std;
int main()
{
    int n;
    int N;
    scanf("%d", &N);
    for (int k = 1; k <= N; k++)
    {
        scanf("%d", &n);
        double sum = 0;
        for (int i = 1; i <= n; i++)
            sum += log(i) / log(10);
        printf("%d\n", (int)sum + 1);
    }
}
