#include <cmath>
#include <iostream>
#define EARTH_R 6371
using namespace std;
struct position
{
    int num;
    char name[36];
    double x;
    double y;
};
double distance(position a, position b)
{
    double d;
    d = acos((sin(a.y) * sin(b.y)) + (cos(a.y) * cos(b.y) * cos(a.x - b.x)));
    return d * EARTH_R;
}
int main()
{
    //嗷嗷。
    int n;
    scanf("%d", &n);
    position list[n];
    for (int i = 0; i < n; i++)
    {
        list[i].num = i;
        scanf("%s", list[i].name);
        scanf("%lf%lf", &list[i].x, &list[i].y);
    }
    cout << distance(list[1], list[0]) << endl;
}
