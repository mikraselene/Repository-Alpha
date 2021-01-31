#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<enable_if<true, int>::type> a;
    a.clear();
}