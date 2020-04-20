#include <iostream>
using namespace std;
int main()
{
    int length, width;
    bool flag = 1;
    do
    {
        cin >> length >> width;
        try
        {
            if (!((length > 1) && (width > 1)))
            {
                throw - 1;
            }
        }
        catch (int error)
        {
            if (error == -1)
            {
                printf("Please input again: \n");
                continue;
            }
        }
        flag = 0;
        break;
    } while (flag == 0);
}
