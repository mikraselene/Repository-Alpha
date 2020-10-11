#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct TreeNode
{
	int data;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int d)
	{
		data = d;
		left = NULL;
		right = NULL;
	}
};

class Tree
{
public:
	Tree(vector<int> v)
	{
		head = Vec2BST(v);
	}
	TreeNode *Vec2BST(vector<int> v)
	{
		if (v.empty())
		{
			return NULL;
		}
		sort(v.begin(), v.end());
		TreeNode *hh = new TreeNode(v[v.size() / 2]);
		vector<int> vec_l = vector<int>(v.begin(), v.begin() + v.size() / 2);
		vector<int> vec_r = vector<int>(v.begin() + v.size() / 2 + 1, v.end());
		hh->left = Vec2BST(vec_l);
		hh->right = Vec2BST(vec_r);
		return hh;
	}
	int Height()
	{
		return height(head);
	}

private:
	int height(TreeNode *node)
	{
		if (node == NULL)
		{
			return 0;
		}
		else
		{
			int lh = height(node->left);
			int rh = height(node->right);
			if (lh > rh)
			{
				return (lh + 1);
			}
			else
			{
				return (rh + 1);
			}
		}
	}
	TreeNode *head;
};

int main()
{
	int n;
	cin >> n;
	while (n--)
	{
		string x;
		getline(cin, x);
		vector<int> k;
		while (1)
		{
			int num = stoi(x.substr(0, x.find(" ")));
			x = x.substr(x.find(" ") + 1, x.size() - x.find(" "));
			k.push_back(num);
			if (x.find(" ") == string::npos)
			{
				break;
			}
		}
		Tree t(k);
		cout << t.Height() << endl;
	}
}
