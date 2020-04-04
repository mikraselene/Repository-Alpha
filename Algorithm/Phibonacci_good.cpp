// define Φ(k, n) = (Φ(k, n - 1) + Φ(k, n - 2)) mod k
#include <iostream>
struct MATRIX
{
    int mat[2][2];
};

int k = 0;

MATRIX Multiply(MATRIX X, MATRIX Y)
{
    MATRIX product;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            product.mat[i][j] = 0;
            for (int m = 0; m < 2; m++)
            {
                product.mat[i][j] += ((X.mat[i][m] * Y.mat[m][j])) % k;
            }
        }
    }
    return product;
}
MATRIX power(MATRIX A, int n)
{
    MATRIX E;
    E.mat[0][0] = 1;
    E.mat[0][1] = 0;
    E.mat[1][0] = 0;
    E.mat[1][1] = 1;
    while (n > 0)
    {
        if (n & 1)
        {
            E = Multiply(E, A);
        }
        A = Multiply(A, A);
        n >>= 1;
    }
    return E;
}
int main()
{
    int k, num;
    scanf("%d%d", &k, &num);
    for (int n = 1; n <= num; n++)
    {
        MATRIX x;
        x.mat[0][0] = 1;
        x.mat[0][1] = 1;
        x.mat[1][0] = 1;
        x.mat[1][1] = 0;
        x = power(x, n - 2);
        printf("Φ(%d, %d) = %d\n", k, n, (x.mat[0][0] + x.mat[0][1]) % k);
    }
    return 0;
}
