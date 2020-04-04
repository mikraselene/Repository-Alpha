#include <cmath>
#include <iostream>
#define A 28
int main()
{
    long int N = pow(2, A);
    double sum = 0;
    for (int i = 1; i <= N; i++)
    {
        sum += 1.0 / i;
    }
    double e = pow((1.0 + 1.0 / N), N);
    double gamma = sum - log(N) / log(e);
    printf("%lf\n", gamma);
}
