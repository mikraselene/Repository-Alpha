#include "../inc/test.h"

void Test(string test)
{
    printf(">> TEST: ");
    printf("%s <<\n", test.c_str());
}

void Test(string test, int data)
{
    printf(">> TEST: ");
    printf("%s = %d <<\n", test.c_str(), data);
}
