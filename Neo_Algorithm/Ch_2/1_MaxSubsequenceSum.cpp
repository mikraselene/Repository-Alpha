#include <iostream>
#include <vector>

int Sub1(std::vector<int> A, int lo, int hi)
{
    int maxLoSum = 0;
    int maxHiSum = 0;
    int maxLoBorderSum = 0;
    int maxHiBorderSum = 0;
    int loBorderSum = 0;
    int hiBorderSum = 0;
    int mid = (lo + hi) / 2;
    if (lo == hi)
    {
        if (A[lo] > 0)
        {
            return A[lo];
        }
        else
        {
            return 0;
        }
    }
    maxLoSum = Sub1(A, lo, mid);
    maxHiSum = Sub1(A, mid + 1, hi);
    for (int i = mid; i >= lo; i--)
    {
        loBorderSum += A[i];
        if (loBorderSum > maxLoBorderSum)
        {
            maxLoBorderSum = loBorderSum;
        }
    }
    for (int i = mid + 1; i <= hi; i++)
    {
        hiBorderSum += A[i];
        if (hiBorderSum > maxHiBorderSum)
        {
            maxHiBorderSum = hiBorderSum;
        }
    }
    return std::max(std::max(maxLoSum, maxHiSum), maxLoBorderSum + maxHiBorderSum);
}
int MSS1(std::vector<int> A)
{
    return Sub1(A, 0, A.size() - 1);
}

int MSS2(std::vector<int> A)
{
    int N = A.size();
    int thisSum = 0;
    int maxSum = 0;
    for (int i = 0; i < N; i++)
    {
        thisSum += A[i];
        if (thisSum > maxSum)
        {
            maxSum = thisSum;
        }
        else if (thisSum < 0)
        {
            thisSum = 0;
        }
    }
    return maxSum;
}

int main()
{
    std::vector<int> A = {4, -3, 5, -2, -1, 2, 6, -2};
    std::cout << MSS1(A) << std::endl;
    std::cout << MSS2(A) << std::endl;
}