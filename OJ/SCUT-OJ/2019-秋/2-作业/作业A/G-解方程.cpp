// XYZ+YZZ=532
#include <iostream>
using namespace std;
int main()
{
    int x, y, z, a;
    for (x = 0; x <= 9; x++)
    {
        for (y = 0; y <= 9; y++)
        {
            for (z = 0; z <= 9; z++)
            {
                a = (x + y) * 100 + (y + z) * 10 + 2 * z;
                if (a == 532)
                {
                    cout << "X:" << x << " Y:" << y << " Z:" << z << endl;
                }
            }
        }
    }
}
