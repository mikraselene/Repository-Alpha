#include <iostream>

#define BOLD "\e[1m"
#define FAINT "\e[2m"
#define ITALIC "\e[3m"
#define UNDERLINE "\e[4m"
#define BLINK "\e[5m"
#define BLINKFAST "\e[6m"
#define NEGATIVE "\e[7m"
#define CONCEAL "\e[8m"
#define STRIKE "\e[9m"
#if 0
#define BLACK "\e[30m"
#define RED "\e[31m"
#define GREEN "\e[32m"
#define YELLOW "\e[33m"
#define BLUE "\e[34m"
#define MAGENTA "\e[35m"
#define CYAN "\e[36m"
#define WHITE "\e[37m"
#else
#define BLACK "\e[90m"
#define RED "\e[91m"
#define GREEN "\e[92m"
#define YELLOW "\e[93m"
#define BLUE "\e[94m"
#define PURPLE "\e[95m"
#define CYAN "\e[96m"
#define WHITE "\e[97m"
#endif
#define RESET "\e[0m"

using namespace std;
int main()
{
    for (int i = 0; i <= 255; i++)
    {
        const char *s = ("\e[48;5;" + to_string(i) + "m").c_str();
        printf("%s", s);
        printf("  " RESET);
        if (i % 64 == 63)
        {
            cout << endl;
        }
    }
}
