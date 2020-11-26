#include <iostream>
#include <list>
using namespace std;

class HashSet
{
public:
    HashSet()
    {
        range = 997;
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
    bool Contains(int key)
    {
        list<int> *bucket = buckets + Hash(key);
        return find(bucket->begin(), bucket->end(), key) != bucket->end();
    }

private:
    int Hash(int key)
    {
        return key % range;
    }
    int range;
    list<int> *buckets;
};

class HashMap
{
public:
    HashMap()
    {
        range = 1000000;
        buckets = new int[range];
        memset(buckets, -1, range * sizeof(int));
    }
    void Put(int key, int value)
    {
        buckets[Hash(key)] = value;
    }
    int Get(int key, int value)
    {
        return buckets[Hash(key)];
    }
    void Remove(int key)
    {
        buckets[Hash(key)] = -1;
    }

private:
    int Hash(int key)
    {
        return key % range;
    }
    int range;
    int *buckets;
};

int main()
{
}