#include <iostream>
using namespace std;
int main()
{
    int n;
    double max, min, a = 0, b = 0, c = 0, d = 0, e = 0;
    double score[1000];
    while (cin >> n)
    {
        for (int i = 1; i <= n; i++)
        {
            cin >> score[i];
            score[0] = score[1];
            if (i == 1)
            {
                max = score[1];
                min = score[1];
            }
            if (score[i] > max)
                max = score[i];
            if (score[i] < min)
                min = score[i];
            if (score[i] <= 100 && score[i] >= 90)
                a++;
            if (score[i] <= 89 && score[i] >= 80)
                b++;
            if (score[i] <= 79 && score[i] >= 70)
                c++;
            if (score[i] <= 69 && score[i] >= 60)
                d++;
            if (score[i] < 60)
                e++;
        }
        cout << "A " << a << endl;
        cout << "B " << b << endl;
        cout << "C " << c << endl;
        cout << "D " << d << endl;
        cout << "E " << e << endl;
        cout << max << " " << min;
    }
}
