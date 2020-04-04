#include <iostream>
using namespace std;
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        int h1, m1, s1;
        scanf("%d%d%d", &h1, &m1, &s1);
        int h2, m2, s2;
        scanf("%d%d%d", &h2, &m2, &s2);
        int tempm, temph;
        int h, m, s;
        s = (s1 + s2) % 60;
        tempm = (s1 + s2) / 60;
        m = (m1 + m2 + tempm) % 60;
        temph = (m1 + m2 + tempm) / 60;
        h = h1 + h2 + temph;
        printf("%d %d %d\n", h, m, s);
    }
}
