#include <iostream>
#include <cmath>
#include <unordered_set>
#include <unordered_map>
#include <vector>
using namespace std;

int f(int s)
{
    int ret = 0;
    while (s)
    {
        ret += pow((s % 10), 2);
        s /= 10;
    }
    return ret;
}

bool g(int n)
{
    unordered_set<int> x;
    while (true)
    {
        if (n == 1)
        {
            return true;
        }
        if (x.find(n) != x.end())
        {
            return false;
        }
        x.insert(n);
        n = f(n);
    }
}

vector<string> findRestaurant(vector<string> &list1, vector<string> &list2)
{
    unordered_map<string, int> ls;
    int min = list1.size() + list2.size();
    vector<string> res;
    for (int i = 0; i < list1.size(); i++)
    {
        ls.insert({list1[i], i});
    }
    for (int i = 0; i < list2.size(); i++)
    {
        if (find(list1.begin(), list1.end(), list2[i]) == list1.end())
        {
            continue;
        }
        int t = ls[list2[i]] + i;
        if (t <= min)
        {
            if (t < min)
            {
                res.clear();
            }
            min = t;
            res.push_back(list2[i]);
        }
    }
    return res;
}

int main()
{
    vector<string> a = {"Shogun", "Tapioca Express", "Burger King", "KFC"};
    vector<string> b = {"KFC", "Shogun", "Burger King"};
    cout << findRestaurant(a, b)[0];
}