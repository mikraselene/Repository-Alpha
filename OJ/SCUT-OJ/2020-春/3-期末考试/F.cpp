#include <iostream>

using namespace std;

template <class T>
class Matrix
{
public:
    Matrix(int n)
    {
        this->n = n;
    }
    void SetMatrix()
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cin >> mat[i][j];
            }
        }
    }
    void Print()
    {
        for (int j = 0; j < n; j++)
        {
            T max = 0;
            for (int i = 0; i < n; i++)
            {
                if (mat[i][j] > max)
                {
                    max = mat[i][j];
                }
            }
            cout << max;
            if (j != n - 1)
            {
                cout << " ";
            }
        }
        cout << endl;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout << mat[n - j - 1][i];
                if (j != n - 1)
                {
                    cout << " ";
                }
            }
            cout << endl;
        }
    }

private:
    int n;
    T mat[1000][1000];
};

int main()
{
    int n;
    while (cin >> n)
    {
        Matrix<int> X(n);
        X.SetMatrix();
        X.Print();
        Matrix<char> Y(n);
        Y.SetMatrix();
        Y.Print();
    }
}