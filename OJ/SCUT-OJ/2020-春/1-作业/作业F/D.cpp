#include <iostream>
using namespace std;
int main()
{
    string temp;
    while (getline(cin, temp))
    {
        for (int i = 0; i < temp.size() / 16; i++)
        {
            printf("%08x  ", (i + 1) * 16);
            for (int j = 0; j < 16; j++)
            {
                printf("%02x ", temp[i * 16 + j]);
            }
            printf(" ");
            for (int j = 0; j < 16; j++)
            {
                printf("%c", temp[i * 16 + j]);
            }
            printf("\n");
        }
    }
}