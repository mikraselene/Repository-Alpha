#include <cstring>
#include <iostream>
using namespace std;
void input(string &a, char b[])
{
    string s;
    getline(cin, s);
    while (s != "START")
    {
        getline(cin, s);
    }
    a = "";
    while (getline(cin, s))
    {
        if (s == "END")
        {
            break;
        }
        a += s + '\n';
    }
    int i = 0;
    int j = 0;
    while (a[i])
    {
        if (a[i] != ' ' && a[i] != '\t' && a[i] != '\n')
        {
            b[j] = a[i];
            j++;
        }
        i++;
    }
    b[j] = '\0';
}
int main()
{
    int n;
    cin >> n;
    string a1, a2;
    char b1[6000], b2[6000];
    while (n--)
    {
        input(a1, b1);
        input(a2, b2);
        if (a1 == a2)
        {
            printf("Accepted\n");
        }
        else if (!strcmp(b1, b2))
        {
            printf("Presentation Error\n");
        }
        else
        {
            printf("Wrong Answer\n");
        }
    }
}
