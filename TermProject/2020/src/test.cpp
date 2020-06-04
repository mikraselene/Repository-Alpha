//OK
#include "../inc/test.h"

Test::Test(const int &data)
{
    printf(">> TEST: ");
    printf("%d <<\n", data);
    getchar();
}

Test::Test(const std::string &test)
{
    printf(">> TEST: ");
    printf("%s <<\n", test.c_str());
    getchar();
}

Test::Test(const std::string &test, const int &data)
{
    printf(">> TEST: ");
    printf("%s = %d <<\n", test.c_str(), data);
    getchar();
}
