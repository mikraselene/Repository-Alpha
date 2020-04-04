#include <cmath>
#include <iostream>
using namespace std;
#define ll long long
int main()
{
    int n;
    scanf("%d", &n);
    while (n--)
    {
        int h, m, s;
        scanf("%d%d%d", &h, &m, &s);
        int t = 3600 * (h % 12) + 60 * m + s;
        double aoh = t * 360.0 / 43200;
        double aom = (t % 3600) * 360.0 / 3600;
        double a = fabs(aoh - aom);
        printf("%d\n", (int)min(a, 360 - a));
    }
}
