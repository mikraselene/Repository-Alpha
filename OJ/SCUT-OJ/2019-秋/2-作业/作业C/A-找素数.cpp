#include <cmath>
#include <iostream>
using namespace std;
bool is_prime(int n)
{
    int k = sqrt(n);
    int i;
    for (i = 2; i <= k; i++)
    {
        if (n % i == 0)
        {
            break;
        }
    }
    return (i > k);
}

int main()
{
    int a;
    while (cin >> a)
    {
        bool flag = 0;
        int list[a + 1];
        for (int i = 1; i <= a; i++)
        {
            cin >> list[i];
        }
        for (int i = 1; i <= a; i++)
        {
            for (int j = 1; j < i; j++)
            {
                if (list[i] == list[j])
                {
                    flag = 1;
                }
            }
            if (is_prime(list[i]) && flag == 0)
            {
                cout << list[i] << " ";
            }
            flag = 0;
        }
        cout << endl;
    }
}
