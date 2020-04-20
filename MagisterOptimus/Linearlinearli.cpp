#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;
int n;
bool flag;
double det, matrix_det;
double initial_elements[100][100], store[100][100];
double operating_elements[100][100], adj_elements[100][100];
void initialize()
{
    for (int x = 1; x <= n; x++)
    {
        for (int y = 1; y <= n; y++)
        {
            initial_elements[x][y] = store[x][y];
        }
    }
}
void input()
{
    printf("Please input the order of A:\nn = ");
    scanf("%d", &n);
    for (int x = 1; x <= n; x++)
    {
        for (int y = 1; y <= n; y++)
        {
            scanf("%lf", &initial_elements[x][y]);
            store[x][y] = initial_elements[x][y];
        }
    }
}
void transform(double a[100][100])
{
    double ratio = 1;
    for (int t = 1; t <= n; t++)
    {
        for (int x = t + 1; x <= n; x++)
        {
            if (a[t][t] == 0)
            {
                for (int i = t + 1; i <= n; i++)
                {
                    if (a[i][t] != 0)
                    {
                        flag = !flag;
                        for (int j = t; j <= n; j++)
                        {
                            a[0][j] = a[i][j];
                            a[i][j] = a[t][j];
                            a[t][j] = a[0][j];
                            ratio = (a[x][t] / a[t][t]);
                        }
                        break;
                    }
                    else
                    {
                        det = 0;
                    }
                }
            }
            else
            {
                ratio = (a[x][t] / a[t][t]);
            }
            for (int y = t; y <= n; y++)
            {
                a[x][y] = a[x][y] - ratio * a[t][y];
            }
        }
    }
}
double determinant(int x, int y)
{
    flag = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (i < x && j < y)
            {
                operating_elements[i][j] = initial_elements[i][j];
            }
            if (i >= x && j < y)
            {
                operating_elements[i][j] = initial_elements[i + 1][j];
            }
            if (i < x && j >= y)
            {
                operating_elements[i][j] = initial_elements[i][j + 1];
            }
            if (i >= x && j >= y)
            {
                operating_elements[i][j] = initial_elements[i + 1][j + 1];
            }
        }
    }
    det = 1;
    transform(operating_elements);
    for (int i = 1; i <= n; i++)
    {
        det = det * operating_elements[i][i];
    }
    det = pow(-1, flag) * det;
    initialize();
    return det;
}
void adjugate()
{
    for (int x = 1; x <= n; x++)
    {
        for (int y = 1; y <= n; y++)
        {
            initialize();
            n--;
            adj_elements[x][y] = determinant(x, y);
            n++;
        }
    }
}
void display_up_border()
{
    printf("          ");
    if (n == 1)
    {
        printf("_        _");
    }
    else
    {
        for (int x = 1; x <= n; x++)
        {
            if (x == 1)
            {
                printf("_       ");
            }
            else if (x == n)
            {
                printf("         _");
            }
            else
            {
                printf("        ");
            }
        }
    }
    printf("\n");
}
void display_down_border()
{
    printf("          ");
    if (n == 1)
    {
        printf("-        -");
    }
    else
    {
        for (int x = 1; x <= n; x++)
        {
            if (x == 1)
            {
                printf("-       ");
            }
            else if (x == n)
            {
                printf("         -");
            }
            else
            {
                printf("        ");
            }
        }
    }
    printf("\n");
}
void display()
{
    if (matrix_det == 0)
    {
        printf("\ndet(A) = 0\n");
    }
    else
    {
        printf("\ndet(A) = %g\n", matrix_det);
    }
    display_up_border();
    for (int x = 1; x <= 2 * n - 1; x++)
    {
        {
            if (x == 1)
            {
                printf("adj(A) = |");
            }
            else
            {
                printf("         |");
            }
        }

        int m = (x + 1) / 2;
        for (int y = 1; y <= n; y++)
        {
            if (x % 2 == 0)
            {
                printf("        ");
            }
            else
            {
                if (adj_elements[y][m] == 0)
                {
                    printf("       0");
                }
                else
                {
                    printf("%8g", pow(-1, m + y) * adj_elements[y][m]);
                }
            }
        }
        printf("  |\n");
    }
    display_down_border();

    if (matrix_det != 0)
    {
        display_up_border();
        for (int x = 1; x <= 2 * n - 1; x++)
        {
            if (x == 1)
            {
                printf("inv(A) = |");
            }
            else
            {
                printf("         |");
            }
            int m = (x + 1) / 2;
            for (int y = 1; y <= n; y++)
            {
                if (x % 2 == 0)
                {
                    printf("        ");
                }
                else
                {

                    adj_elements[y][m] = pow(-1, m + y) * adj_elements[y][m];
                    if (adj_elements[y][m] == 0)
                    {
                        printf("       0");
                    }
                    else
                    {
                        printf("%8.3f", adj_elements[y][m] / matrix_det);
                    }
                }
            }
            printf("  |\n");
        }
        display_down_border();
    }
    else
    {
        printf("inv(A) do not exist.\n");
    }
    printf("\n");
    printf("Press ENTER to restart...");
}

int main()
{
    do
    {
        system("clear");
        input();
        matrix_det = determinant(n + 1, n + 1);
        adjugate();
        display();
        cin.get();
    } while (cin.get());
}
