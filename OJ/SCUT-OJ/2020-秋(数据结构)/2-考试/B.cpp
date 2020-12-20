#include <iostream>
#include <list>
using namespace std;
int main()
{
    int t = 0;
    cin >> t;
    while (t--)
    {
        int m, n;
        cin >> m >> n;
        list<int> a, b;
        while (m--)
        {
            int k;
            cin >> k;
            a.push_back(k);
        }
        while (n--)
        {
            int k;
            cin >> k;
            b.push_back(k);
        }
        a.sort();
        b.sort();
        a.merge(b);
        a.sort();
        list<int>::iterator i = a.begin();
        while (true)
        {
            cout << *i;
            if (++i == a.end())
            {
                break;
            }
            cout << " ";
        }
        cout << endl;
    }
}