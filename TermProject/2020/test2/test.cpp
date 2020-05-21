#include <iostream>
#include <numeric>
#include <iomanip>
#include <algorithm>
using namespace std;

void print(double *x)
{
}
int main()
{
    int k = 9;
    double *per =
        new double[k]{12, 30, 40, 53, 22, 52, 11, 40, 23};
    double p[k];
    double sum = accumulate(per, per + k, 0);
    double max = 0;
    for (int i = 0; i < k; i++)
    {
        if (max < per[i])
        {
            max = per[i];
        }
    }
    for (int i = 0; i < k; i++)
    {
        p[i] = per[i] / sum;
        cout
            << fixed << setprecision(2) << setw(5) << setiosflags(ios::right)
            << p[i] * 100 << "% ";
        cout << "[";
        for (int j = 0; j < p[i] * 30 / (max / sum); j++)
        {
            cout << "#";
        }
        cout << "]";
        cout << endl;
    }
}

/*

2020.5  
2020.4  
2020.3  
2020.2  
2020.1  


*/