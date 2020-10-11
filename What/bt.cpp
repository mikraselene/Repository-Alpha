#include <iostream>
#include <vector>
using namespace std;

#define XX -2147483648

enum
{
	PRE_ORDER,
	IN_ORDER,
	POST_ORDER,
};

template <class T>
class BinaryTree
{
public:
	BinaryTree(vector<T> t)
	{
		tree = t;
		n = t.size();
	}
	int Parent(int r)
	{
		return (r - 1) / 2;
	}
	int LChild(int r)
	{
		return 2 * r + 1 < n ? 2 * r + 1 : -1;
	}
	int RChild(int r)
	{
		return 2 * r + 2 < n ? 2 * r + 2 : -1;
	}
	int LSibling(int r)
	{
		return r % 2 == 0 ? r - 1 : -1;
	}
	int RSibling(int r)
	{
		return r % 2 == 1 && r + 1 < n ? r + 1 : -1;
	}
	void Print(int flag)
	{
		Traverse(0, flag);
	}

private:
	void
	Traverse(int k, int flag)
	{
		if (k == n || k == -1 || tree[k] == XX)
		{
			return;
		}
		if (flag == PRE_ORDER)
		{
			cout << tree[k] << " ";
		}
		Traverse(LChild(k), flag);
		if (flag == IN_ORDER)
		{
			cout << tree[k] << " ";
		}
		Traverse(RChild(k), flag);
		if (flag == POST_ORDER)
		{
			cout << tree[k] << " ";
		}
	}
	vector<T> tree;
	int n;
};

int main()
{
	vector<int> t = {0, 1, 2, 3, 4, XX, 6, 7, 8, 9, XX, 11};
	BinaryTree<int> BT(t);
	BT.Print(PRE_ORDER);
}
