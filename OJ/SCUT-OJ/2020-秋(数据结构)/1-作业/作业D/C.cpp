#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

void Func(vector<int> &arr, int len, int index)
{
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    int minIdx = index;
    if (left < len && arr[left] < arr[minIdx])
    {
        minIdx = left;
    }
    if (right < len && arr[right] < arr[minIdx])
    {
        minIdx = right;
    }

    if (minIdx != index)
    {
        swap(arr[minIdx], arr[index]);
        Func(arr, len, minIdx);
    }
}

void HeapSort(vector<int> &arr, int size)
{
    for (int i = size / 2 - 1; i >= 0; i--)
    {
        Func(arr, size, i);
    }
    for (int i = 0; i < size; i++)
    {
        if (i != 0)
        {
            cout << " ";
        }
        cout << arr[i];
    }
    cout << endl;
    for (int i = size - 1; i >= 1; i--)
    {
        swap(arr[0], arr[i]);
        Func(arr, i, 0);
    }
}

int main()
{
    vector<int> arr;
    string str;
    getline(cin, str);
    stringstream ss(str);
    int temp;
    for (; ss >> temp;)
    {
        arr.push_back(temp);
    }
    int size = arr.size();
    HeapSort(arr, size);
    for (int i = 0; i < size; i++)
    {
        if (i != 0)
        {
            cout << " ";
        }
        cout << arr[i];
    }
}