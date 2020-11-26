#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;
int Partition(vector<int> arr, int low, int high, int last)
{
    do
    {
        while (arr[low] < last)
        {
            low++;
        }
        while (high && arr[high] >= last)
        {
            high--;
        }
        swap(arr[low], arr[high]);
    } while (low < high);
    swap(arr[low], arr[high]);
    return low;
}

vector<int> arr(1000);
string str;
int main()
{
    int n;
    int m;
    cin >> m;
    getline(cin, str);
    while (m--)
    {
        getline(cin, str);
        stringstream ss(str);
        for (n = 0; ss >> arr[n]; ++n)
            ;
        cout << Partition(arr, 0, n - 1, arr[n - 1]) << endl;
    }
}
