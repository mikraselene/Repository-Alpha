#include <iostream>
using namespace std;
struct mat
{
    int a[2][2];
};

mat multiply(mat x, mat y)
{
    mat product;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            product.a[i][j] = 0;
            for (int k = 0; k < 2; k++)
            {
                product.a[i][j] += (x.a[i][k] * y.a[k][j]) % 7;
            }
        }
    }
    return product;
}

mat power(mat x, int n)
{
    mat e;
    e.a[0][0] = 1;
    e.a[0][1] = 0;
    e.a[1][0] = 0;
    e.a[1][1] = 1;
    while (n)
    {
        if (n % 2 == 1)
        {
            e = multiply(e, x);
        }
        x = multiply(x, x);
        n /= 2;
    }
    return e;
}

int main()
{
    int A, B, n;
    while (cin >> A >> B >> n && (A || B || n))
    {
        mat x;
        x.a[0][0] = A;
        x.a[0][1] = B;
        x.a[1][0] = 1;
        x.a[1][1] = 0;
        x = power(x, n - 2);
        cout << (x.a[0][0] + x.a[0][1]) % 7 << endl;
    }
}
