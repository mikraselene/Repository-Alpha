#include <iostream>
#include <numeric>
#include <iomanip>
#include <algorithm>
using namespace std;

class Bill
{
private:
    double amount;
    int type;
    string info;
    //Date date;
};

int main()
{
}

/*

2020.5  
2020.4  
2020.3  
2020.2  
2020.1  
class K
{
public:
    K(const int &s)
    {
        data = s;
    }
    void Print() const
    {
        cout << data;
    }

private:
    int data;
};
int main()
{
    double per[] = {12, 30, 40, 53, 22, 52, 11, 40, 23};
    int k = sizeof(per) / 8;
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

*/