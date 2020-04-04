#include <cmath>
#include <iostream>
using namespace std;
int main()
{
    int hrz_levm, hrz_levn;
    int left_levm, left_levn;
    int right_levm, right_levn;
    int m, n;
    while (~scanf("%d%d", &m, &n))
    {
        hrz_levm = ceil(sqrt(m));
        hrz_levn = ceil(sqrt(n));
        left_levm = (m + 1 - pow(hrz_levm - 1, 2)) / 2;
        left_levn = (n + 1 - pow(hrz_levn - 1, 2)) / 2;
        right_levm = (pow(hrz_levm, 2) - m) / 2 + 1;
        right_levn = (pow(hrz_levn, 2) - n) / 2 + 1;
        int hrz = abs(hrz_levm - hrz_levn);
        int left = abs(left_levm - left_levn);
        int right = abs(right_levm - right_levn);
        printf("%d\n", hrz + left + right);
    }
}
