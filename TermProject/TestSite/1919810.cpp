#include <iostream>
using namespace std;

void func(const char (*cp)[5])
{
    for (int i = 0; i <= 2; i++)
    {
        for (int j = 0; j <= 4; j++)
        {
            cout << cp[i][j];
        }
        cout << endl;
    }
}

int main()
{
    char i[3][5] = {{'A', 'B', 'X', 'D', 'E'}, {'a', 'b', 'X', 'd', 'e'}, {'a', 'b', 'g', 'd', 'e'}};
    func(i);
    bool flag = 1;
    cout << flag;
    flag = !flag;
    cout << flag;
}
