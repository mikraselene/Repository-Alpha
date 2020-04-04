#include <iostream>
using namespace std;
int main()
{
    int t, n;
    int j = 1;
    int arr[200000];
    cin >> t;
    while (t--)
    {
        cin >> n;
        for (int i = 1; i <= n; i++)
        {
            cin >> arr[i];
        }
        int sum = arr[1];
        int begin = 1;
        int end = 1;
        int temp = 1;
        for (int i = 2; i <= n; i++)
        {
            if (arr[i - 1] >= 0)
            {
                arr[i] += arr[i - 1];
            }
            else
            {
                temp = i;
            }
            if (arr[i] > sum)
            {
                sum = arr[i];
                begin = temp;
                end = i;
            }
        }
        cout << "Case " << j << ":" << endl;
        cout << sum << " " << begin << " " << end << endl;
        j++;
        if (t != 0)
        {
            cout << endl;
        }
    }
}
