#include <iostream>
#include <memory.h>
using namespace std;

#define N 10000000000

int test_strncmp()
{
	int begin = time(0);
	for (long long i = 1; i <= N; i++)
	{
		char *x = "return";
		x++;
		bool flag = strncmp(x, "eturn", 5);
	}
	int end = time(0);
	return end - begin;
}

int test_memcmp()
{
	int begin = time(0);
	for (long long i = 1; i <= N; i++)
	{
		char *x = "return";
		x++;
		bool flag = memcmp(x, "eturn", 5);
	}
	int end = time(0);
	return end - begin;
}

int test()
{
	int begin = time(0);
	for (long i = 1; i <= N; i++)
	{
		char *x = "return";
		x++;
		bool flag = x[0] == 'e' && x[1] == 't' && x[2] == 'u' && x[3] == 'r' && x[4] == 'n';
	}
	int end = time(0);
	return end - begin;
}

int main()
{
	//cout << test_strncmp() << endl;
	cout << test_memcmp() << endl;
	//cout << test() << endl;
}