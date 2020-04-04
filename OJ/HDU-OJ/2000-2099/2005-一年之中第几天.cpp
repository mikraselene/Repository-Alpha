#include <cmath>
#include <iostream>
using namespace std;
int main()
{
    int y, m, d;
    while (~scanf("%d/%d/%d", &y, &m, &d))
    {
        int flag = 0;
        int day = 0;
        if ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0)
        {
            flag = 1;
        }
        int i;
        for (i = 1; i <= m - 1; i++)
        {
            int j;
            if (i == 2)
            {
                j = 28 + flag;
            }
            else if (i == 4 || i == 6 || i == 9 || i == 11)
            {
                j = 30;
            }
            else
                j = 31;
            day = day + j;
        }
        day = day + d;
        cout << day << endl;
    }
}
