#include <iostream>
#include <vector>
#include <list>
using namespace std;

class HashSet
{
public:
    HashSet(int m, int k)
    {
        range = m;
        slot = k;
        buckets = new list<int>[range];
    }
    void Add(int key)
    {
        buckets[Hash(key)].push_back(key);
    }
    void Remove(int key)
    {
        buckets[Hash(key)].remove(key);
    }
    int Size()
    {
        return buckets[slot].size();
    }

private:
    int Hash(int key)
    {
        return key % range;
    }
    int range;
    int slot;
    list<int> *buckets;
};

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, m, k;
        cin >> n >> m >> k;
        HashSet s(m, k);
        while (n--)
        {
            int x;
            cin >> x;
            s.Add(x);
        }
        cout << s.Size() << endl;
    }
}
