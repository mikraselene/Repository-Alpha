#include <cstring>
#include <iostream>
using namespace std;
string cuneiform[37] = {"𐎠", "𐎡", "𐎢", "𐎣", "𐎤", "𐎥", "𐎦", "𐎧", "𐎨", "𐎩", "𐎪", "𐎫", "𐎬", "𐎭", "𐎮", "𐎯", "𐎰", "𐎱", "𐎲",
                        "𐎳", "𐎴", "𐎵", "𐎶", "𐎷", "𐎸", "𐎹", "𐎺", "𐎻", "𐎼", "𐎽", "𐎾", "𐎿", "𐏀", "𐏁", "𐏂", "𐏃", "𐏐"};
string latin[37] = {"a", "i", "u", "ka", "ku", "ga", "gu", "xa", "ca", "ja", "ji", "ta", "tu",
                    "da", "di", "du", "tha", "pa", "ba", "fa", "na", "nu", "ma", "mi", "mu", "ya",
                    "va", "vi", "ra", "ru", "la", "sa", "za", "sha", "ssa", "ha", " "};
int s;

int latcmp(string la, int k)
{
    bool flag = 0;
    string temp = la.substr(s, k);
    if (k > 3)
    {
        return -1;
    }
    else
    {
        for (int i = 0; i < 37; i++)
        {
            if (latin[i] == temp)
            {
                flag = 1;
                s += k;
                return i;
            }
        }
        if (flag == 0)
        {
            return latcmp(la, k + 1);
        }
    }
    return 0;
}
int main()
{
    string la;
    while (getline(cin, la))
    {
        s = 0;
        while (1)
        {
            int i = latcmp(la, 1);
            if (i >= 0)
                cout << cuneiform[i] << " ";
            else
                break;
        }
        cout << endl;
    }
}
