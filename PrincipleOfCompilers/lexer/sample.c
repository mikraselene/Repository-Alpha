#include <stdio.h>
void print() { printf("this\n"); }
int main()
{
	int i;
	int n = 1 + 3 * 2 - 5;
	for (i = 1; i <= n; i++)
	{ /*hello*/
		printf("hello world\n");
		print();
	}
	printf("salve munde"); /* salve = hello */
}
