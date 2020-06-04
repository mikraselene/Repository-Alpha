#include <iostream>
#include <fstream>
using namespace std;
int main()
{
    ofstream it;
    it.open("a.txt", ios::out);
    if (!it)
    {
        cout << "error";
    }
    it << 20 << endl;
    it.close();
}