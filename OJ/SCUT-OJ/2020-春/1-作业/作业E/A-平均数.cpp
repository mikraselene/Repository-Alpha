#include <iostream>
using namespace std;

template <class T>
class Average
{
public:
    Average(int num)
    {
        data = 0;
        n = num;
    }
    T PrintAverage()
    {
        return data / n;
    }
    friend istream &operator>>(istream &input, Average<T> &A)
    {
        T temp;
        input >> temp;
        A.data += temp;
        return input;
    }

private:
    T data;
    int n;
};

int main()
{
    bool flag = 0;
    while (cin >> flag)
    {
        int n;
        cin >> n;
        if (flag)
        {
            Average<double> x(n);
            for (int i = 0; i < n; i++)
            {
                cin >> x;
            }
            printf("%.2lf\n", x.PrintAverage());
        }
        else
        {
            Average<int> x(n);
            for (int i = 0; i < n; i++)
            {
                cin >> x;
            }
            printf("%d\n", x.PrintAverage());
        }
    }
}
