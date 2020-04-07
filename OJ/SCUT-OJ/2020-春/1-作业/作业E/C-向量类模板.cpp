#include <iostream>
using namespace std;

template <typename T>
class T_Vector
{
public:
    T_Vector(T *at, T *bt, int nt)
    {
        n = nt;
        a = new int[n];
        b = new int[n];
        result = new int[n];
        for (int i = 0; i < n; i++)
        {
            a[i] = at[i];
            b[i] = bt[i];
        }
    }
    void Add()
    {
        for (int i = 0; i < n; i++)
        {
            result[i] = a[i] + b[i];
        }
        Print();
    }
    void Substract()
    {
        for (int i = 0; i < n; i++)
        {
            result[i] = a[i] - b[i];
        }
        Print();
    }
    void Print()
    {
        cout << result[0];
        for (int i = 1; i < n; i++)
        {
            cout << " " << result[i];
        }
        cout << endl;
    }

private:
    T *a;
    T *b;
    T *result;
    int n;
};

int main()
{
    char k = '+';
    while (cin >> k)
    {
        int m = 0;
        cin >> m;
        int *a = new int[m];
        int *b = new int[m];
        for (int i = 0; i < m; i++)
        {
            cin >> a[i];
        }
        for (int i = 0; i < m; i++)
        {
            cin >> b[i];
        }
        T_Vector<int> v(a, b, m);
        switch (k)
        {
        case '+':
            v.Add();
            break;
        case '-':
            v.Substract();
            break;
        }
    }
}
