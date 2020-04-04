#include <iostream>
using namespace std;
struct milk
{
    char name[200];
    int price;
    int volume;
    int day;
    double factor;
};
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        int n;
        scanf("%d", &n);
        milk a[n];
        double max = 0;
        int k;
        for (int i = 0; i < n; i++)
        {
            cin >> a[i].name;
            scanf("%d%d", &a[i].price, &a[i].volume);
            if (a[i].volume < 200)
                continue;
            a[i].day = a[i].volume / 200;
            if (a[i].day > 5)
                a[i].day = 5;
            a[i].factor = (double)a[i].day / (double)a[i].price;
            if (a[i].factor > max)
            {
                max = a[i].factor;
                k = i;
            }
            else if (a[i].factor == max)
            {
                if (a[i].price < a[k].price)
                    k = i;
                else if (a[i].price == a[k].price)
                {
                    if (a[i].volume > a[k].volume)
                        k = i;
                }
            }
        }
        cout << a[k].name << endl;
    }
}
