#include <iostream>
using namespace std;

int Josephus(int n, int k)
{
	return n > 1 ? (Josephus(n - 1, k) + k) % n : 0;
}
int main()
{
	int n;
	int k;
	while (cin >> n >> k)
	{
		cout << Josephus(n, k) + 1 << endl;
	}
}