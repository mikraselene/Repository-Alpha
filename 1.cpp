#include <iostream>
using namespace std;
int main()
{
    for (int i = 30; i <= 47; i++)
    {
        printf("\\e[%dm: \e[%dm salve munde!\e[0m\n", i, i);
    }
}