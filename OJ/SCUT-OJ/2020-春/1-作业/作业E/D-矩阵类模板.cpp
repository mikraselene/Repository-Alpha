#include <iostream>
using namespace std;

template <typename T>
class T_Matrix
{
public:
    T_Matrix(T **at, T **bt, int mt, int nt)
    {
        m = mt;
        n = nt;
        a = new int *[m];
        b = new int *[m];
        result = new int *[m];
        for (int i = 0; i < n; i++)
        {
            a[i] = new int[n];
            b[i] = new int[n];
            result[i] = new int[n];
        }
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                a[i][j] = at[i][j];
                b[i][j] = bt[i][j];
            }
        }
    }
    void Add()
    {
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                result[i][j] = a[i][j] + b[i][j];
            }
        }
        Print();
    }
    void Substract()
    {
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                result[i][j] = a[i][j] - b[i][j];
            }
        }
        Print();
    }
    void Print()
    {
        for (int i = 0; i < m; i++)
        {
            cout << result[i][0];
            for (int j = 1; j < n; j++)
            {
                cout << " " << result[i][j];
            }
            cout << endl;
        }
    }

private:
    T **a;
    T **b;
    T **result;
    int m;
    int n;
};

int main()
{
    char k = '+';
    while (cin >> k)
    {
        int m = 0;
        int n = 0;
        cin >> m >> n;
        int **a = new int *[m];
        int **b = new int *[m];
        for (int i = 0; i < n; i++)
        {
            a[i] = new int[n];
            b[i] = new int[n];
        }

        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cin >> a[i][j];
            }
        }
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cin >> b[i][j];
            }
        }

        T_Matrix<int> mat(a, b, m, n);

        switch (k)
        {
        case '+':
            mat.Add();
            break;
        case '-':
            mat.Substract();
            break;
        }
    }
}
