#include <algorithm>
#include <iostream>
#include <vector>

bool BinarySearch(std::vector<int> A, int key)
{
    sort(A.begin(), A.end());
    int lo = 0;
    int hi = A.size() - 1;
    int mid = 0;
    while (lo <= hi)
    {
        mid = (lo + hi) / 2;
        if (A[mid] < key)
        {
            lo = mid + 1;
        }
        else if (A[mid] > key)
        {
            hi = mid - 1;
        }
        else
        {
            return mid;
        }
    }
    return 0;
}

int main()
{
    std::vector<int> A = {1, 2, 3, 4, -2, -3, -4, -5};
    int key = 1;
    std::cout << BinarySearch(A, key) << std::endl;
}