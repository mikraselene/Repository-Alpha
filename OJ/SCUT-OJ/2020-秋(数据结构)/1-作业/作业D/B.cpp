#include <iostream>
#include <vector>
#include <sstream>
#include <list>
using namespace std;

class HashSet
{
public:
    HashSet(int m)
    {
        range = m;
        buckets = new int[range];
        occupied = new bool[range];
        for (int i = 0; i < range; i++)
        {
            occupied[i] = false;
        }
    }
    void Add(int key, int t)
    {
        int h = Hash(key);
        if (h + t >= range)
        {
            t -= range;
        }
        if (occupied[h + t] == false)
        {
            occupied[h + t] = true;
            buckets[h + t] = key;
        }
        else
        {
            Add(key, t + 1);
        }
    }

    void Print()
    {
        for (int i = 0; i < range; i++)
        {
            if (occupied[i])
            {
                cout << i << " " << buckets[i] << endl;
            }
        }
    }

private:
    int Hash(int key)
    {
        return key % range;
    }
    int range;
    int *buckets;
    bool *occupied;
};

int main()
{
    string str;
    int n;
    cin >> n;
    HashSet s(n);
    getchar();
    getline(cin, str);
    stringstream ss(str);
    int temp;
    for (int i = 0; ss >> temp; i++)
    {
        s.Add(temp, 0);
    }
    s.Print();
}