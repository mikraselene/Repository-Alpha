#include <iostream>
int main()
{
    double sum = 0, a, b;
    char s[1000];
    while (~scanf("%s%lf %lf", s, &a, &b))
        sum += a * b;
    printf("%.1lf\n", sum);
}
