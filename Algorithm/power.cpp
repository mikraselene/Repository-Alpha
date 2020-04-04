#include <iostream>
using namespace std;
#define MAX_N 100
struct MATRIX
{
    int mat[MAX_N][MAX_N];
};

int n = 0;

MATRIX Multiply(MATRIX X, MATRIX Y)
{
    MATRIX product = {};
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            product.mat[i][j] = 0;
            for (int m = 0; m < n; m++)
            {
                product.mat[i][j] += X.mat[i][m] * Y.mat[m][j];
            }
        }
    }
    return product;
}

MATRIX Power(MATRIX A, int k)
{
    MATRIX E;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            E.mat[i][j] = (i == j);
        }
    }
    while (k > 0)
    {
        if (k & 1)
        {
            E = Multiply(E, A);
        }
        A = Multiply(A, A);
        k >>= 1;
    }
    return E;
}

int main()
{
    int n = 0;
    printf("n = ");
    while (~scanf("%d", &n))
    {
        int k = 0;
        printf("k = ");
        scanf("%d", &k);
        MATRIX A = {};
        printf("A = \n");
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                scanf("%d", &A.mat[i][j]);
            }
        }
        A = Power(A, k);
        printf("A ^ %d = \n", k);
        int sum = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                sum += A.mat[i][j];
                if (A.mat[i][j])
                {
                    printf("%d ", A.mat[i][j]);
                }
                else
                {
                    printf("O ");
                }
            }
            printf("\n");
        }
        printf("sum = %d\n\n", sum);
        printf("n = ");
    }
}
