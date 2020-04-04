#include <iostream>
#include <set>
using namespace std;
int main()
{
    int n = 0;
    int m = 0;
    set<int> s;
    while ((cin >> n >> m) && (n || m))
    {
        int element = 0;
        s.clear();
        for (int i = 0; i < n; i++)
        {
            cin >> element;
            s.insert(element);
        }
        for (int i = 0; i < m; i++)
        {
            cin >> element;
            if (s.find(element) != s.end())
            {
                s.erase(element);
            }
        }
        if (s.size() == 0)
        {
            cout << "NULL" << endl;
        }
        else
        {
            set<int>::iterator it = s.begin();
            for (it = s.begin(); it != s.end(); it++)
            {
                cout << *it << " ";
            }
            cout << endl;
        }
    }
}