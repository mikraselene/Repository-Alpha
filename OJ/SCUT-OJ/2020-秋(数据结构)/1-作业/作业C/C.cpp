#include <iostream>
#include <list>
using namespace std;
int main()
{
    int m = 0;
    int n = 0;
    while (cin >> m >> n)
    {
        list<int> a;
        list<int> b;
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
        while (1)
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