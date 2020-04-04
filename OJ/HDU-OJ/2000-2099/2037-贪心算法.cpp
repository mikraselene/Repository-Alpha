#include <algorithm>
#include <iostream>
using namespace std;
struct program
{
	int begin;
	int end;
};
bool cmp(program x, program y)
{
	return (x.end < y.end);
}
int main()
{
	int n;
	while (~scanf("%d", &n) && n)
	{
		program *a = new program[n];
		for (int i = 0; i < n; i++)
		{
			scanf("%d%d", &a[i].begin, &a[i].end);
		}
		sort(a, a + n, cmp);
		int new_end = -1;
		int cnt = 0;
		for (int i = 0; i < n; i++)
		{
			if (a[i].begin >= new_end)
			{
				cnt++;
				new_end = a[i].end;
			}
		}
		printf("%d\n", cnt);
	}
}
