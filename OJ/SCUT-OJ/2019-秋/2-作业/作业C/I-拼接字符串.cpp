#include <iostream>
using namespace std;
void *func(char a[], char b[])
{
    int i, j;
    for (i = 0; a[i] != '\0'; i++)
    {
    }
    for (j = 0; b[j] != '\0'; i++, j++)
    {
        a[i] = b[j];
    }
    a[i] = '\0';
    return a;
}

int main(void)
{
    char a[100], b[100];
    while (cin >> a >> b)
    {
        func(a, b);
        cout << a << endl;
    }
}
