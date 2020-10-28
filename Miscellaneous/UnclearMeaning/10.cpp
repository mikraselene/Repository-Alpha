#include <iostream>
#include <algorithm>
#include <string>
#include <numeric>
#include <sstream>
using namespace std;

string dec2bin(int n)
{
    int i = 0, j = 0;
    int bin[8] = {0};
    i = n;
    while (i)
    {
        bin[j] = i % 2;
        i /= 2;
        j++;
    }
    int s = 0;
    char ba[8];
    for (i = 7; i >= 0; i--)
    {
        if (bin[i] == 1)
        {
            ba[s] = '1';
        }
        else
        {
            ba[s] = '0';
        }

        s++;
    }
    string base(ba);
    return base;
}

string func1(string a, string b)
{
    string base[2];
    base[0] = a;
    base[1] = b;
    string sub[4];
    sub[0] = base[0].substr(0, 8);
    sub[1] = base[0].substr(8, 8);
    sub[2] = base[1].substr(0, 8);
    sub[3] = base[1].substr(8, 8);
    sort(sub, sub + 4);
    string output = accumulate(sub, sub + 4, string(""));
    return output;
}
string func2(string a, string b)
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
    return output.str();
}

bool check(string a, string b)
{
    if (func1(a, b) == func2(a, b))
    {
        return 0;
    }
    else
    {
        cout << a << endl
             << b << endl;
        printf("%s\n", func1(a, b).c_str());
        cout << func2(a, b) << endl;
        cout << "ERROR\n";
        return 1;
    }
}
void generate()
{
    for (int i = 0; i < 256; i++)
    {
        for (int j = i + 1; j < 256; j++)
        {
            for (int k = 0; k < 256; k++)
            {
                for (int l = k + 1; l < 256; l++)
                {
                    string a = dec2bin(i) + dec2bin(j);
                    string b = dec2bin(k) + dec2bin(l);
                    if (check(a, b))
                    {
                        return;
                    }
                }
            }
        }
    }
}
int main()
{

    generate();
    string a = "00000000";
    string b = "00000001";
    string x = a + b;
    string y = "0000000100000010";
    cout << x << endl
         << y << endl;
    cout << func1(x, y) << endl;
    cout << func2(x, y) << endl;
    //cout << dec2bin(123);
    /*
    cout << func1("0000000000000001", "0000000100000010") << endl;
    cout << func2("0000000000000001", "0000000100000010") << endl;
    string x = "0000000000000001";
    string y = "0000000100000010";

    cout << func1(x, y) << endl;
    cout << func2(x, y) << endl;
    

    0000000000000001
    0000000100000010
    0000001000000000000000100000001
    0000000000000001000000010000001
*/
}
