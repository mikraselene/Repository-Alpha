//OK
#include "../inc/test.h"

void Test(const int &data)
{
    printf(">> TEST: ");
    printf("%d <<\n", data);
    getchar();
}

void Test(const std::string &test)
{
    printf(">> TEST: ");
    printf("%s <<\n", test.c_str());
    getchar();
}

void Test(const std::string &test, const int &data)
{
    printf(">> TEST: ");
    printf("%s = %d <<\n", test.c_str(), data);
    getchar();
}
