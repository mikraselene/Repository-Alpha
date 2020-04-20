#include <iostream>
#include <string>
#include <sstream>
using namespace std;
int main()
{
    string a, b;
    while (cin >> a >> b)
    {
        string c, d;
        ostringstream output;
        int n1 = a.size() / 8, n2 = b.size() / 8, maxx, minn;
        if (n1 > n2)
            maxx = n1, minn = n2, c = a, d = b;
        else
            maxx = n2, minn = n1, c = b, d = a;
        for (int i = 0, j = 0; i < maxx || j < minn;)
        {
            string x, y;
            if (j < minn && i < maxx)
            {
                x = c.substr(i * 8, 8), y = d.substr(j * 8, 8);
                for (int k = 0; k < 8; k++)
                {
                    if (int(x[k]) < int(y[k]))
                    {
                        output << x;
                        i++;
                        break;
                    }
                    else if (int(x[k]) > int(y[k]))
                    {
                        output << y;
                        j++;
                        break;
                    }
                    if (k == 7 && int(x[k]) == int(y[k]))
                    {
                        output << x << y;
                        i++, j++;
                    }
                }
            }
            else if (j >= minn)
            {
                string x = c.substr(i * 8, (maxx - i) * 8);
                output << x;
                break;
            }
            else
            {
                string x = d.substr(j * 8, (minn - j) * 8);
                output << x;
                break;
            }
        }
        cout << output.str() << endl;
    }
}
