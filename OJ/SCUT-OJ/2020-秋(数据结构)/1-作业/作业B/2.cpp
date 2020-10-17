#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int main()
{
    int n;
    cin >> n;
    while (n--)
    {
        int k;
        vector<int> nums;
        while (cin >> k && k != -1)
        {
            nums.push_back(k);
        }
        for (vector<int>::iterator it = nums.begin(); it != nums.end() && it + 1 != nums.end(); it++, it++)
        {
            swap(*it, *(it + 1));
        }
        for (vector<int>::iterator it = nums.begin(); it != nums.end(); it++)
        {
            cout << *it << " ";
        }
        cout << endl;
    }
}