#include <iostream>
#include <string>
using namespace std;
struct LANG
{
    string Coptic;
    string Latin;
};
LANG t[72] = {
    {"Ⲁ", "A"},
    {"Ⲃ", "B"},
    {"Ⲅ", "G"},
    {"Ⲇ", "D"},
    {"Ⲉ", "E"},
    {"Ⲋ", "St"},
    {"Ⲍ", "Z"},
    {"Ⲏ", "Ee"},
    {"Ⲑ", "Th"},
    {"Ⲓ", "I"},
    {"Ⲕ", "K"},
    {"Ⲗ", "L"},
    {"Ⲙ", "M"},
    {"Ⲛ", "N"},
    {"Ⲝ", "Ks"},
    {"Ⲟ", "O"},
    {"Ⲡ", "P"},
    {"Ⲣ", "R"},
    {"Ⲥ", "S"},
    {"Ⲧ", "T"},
    {"Ⲩ", "U"},
    {"Ⲫ", "Ph"},
    {"Ⲭ", "Kh"},
    {"Ⲯ", "Ps"},
    {"Ⲱ", "Oo"},
    {"Ϣ", "Sh"},
    {"Ϧ", "X"},
    {"Ϩ", "H"},
    {"Ϫ", "J"},
    {"Ϭ", "Q"},
    {"ⲁ", "a"},
    {"ⲃ", "b"},
    {"ⲅ", "g"},
    {"ⲇ", "d"},
    {"ⲉ", "e"},
    {"ⲋ", "st"},
    {"ⲍ", "z"},
    {"ⲏ", "ee"},
    {"ⲑ", "th"},
    {"ⲓ", "i"},
    {"ⲕ", "k"},
    {"ⲗ", "l"},
    {"ⲙ", "m"},
    {"ⲛ", "n"},
    {"ⲝ", "ks"},
    {"ⲟ", "o"},
    {"ⲡ", "p"},
    {"ⲣ", "r"},
    {"ⲥ", "s"},
    {"ⲧ", "t"},
    {"ⲩ", "u"},
    {"ⲫ", "ph"},
    {"ⲭ", "kh"},
    {"ⲯ", "ps"},
    {"ⲱ", "oo"},
    {"ϣ", "sh"},
    {"ϧ", "x"},
    {"ϩ", "h"},
    {"ϭ", "q"},
    {"ϫ", "j"},
    {".", "."},
    {"-", "-"},
    {":", ":"},
    {";", ";"},
    {",", ","},
    {"!", "!"},
    {"?", "?"},
    {"«", "["},
    {"»", "]"},
    {"‹", "("},
    {"›", ")"},
    {" ", " "},
};
int s;
int latcmp(string la, int k)
{
    bool flag = 0;
    string temp = la.substr(s, k);
    if (k < 1)
    {
        return -1;
    }
    else
    {
        for (int i = 0; i < 72; i++)
        {
            if (t[i].Latin == temp)
            {
                flag = 1;
                s += k;
                return i;
            }
        }
        if (flag == 0)
        {
            return latcmp(la, k - 1);
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
            la += "#";
            string end = la.substr(s + 1, 1);
            bool flag = 0;
            if (end == "\0")
            {
                break;
            }

            int i = latcmp(la, 2);
            if (i >= 0)
            {
                cout << t[i].Coptic;
            }
            else
            {
                break;
            }
        }
        cout << endl;
    }
}
