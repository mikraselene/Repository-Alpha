#include <vector>
using namespace std;
class KthLargest
{
    struct TreeNode
    {
        int val;
        int count;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int x) : val(x), left(NULL), right(NULL), count(1) {}
    };

public:
    int K;
    TreeNode *root;
    TreeNode *addNode(TreeNode *root, int val)
    {
        if (!root)
            return new TreeNode(val);
        if (val <= root->val)
        {
            root->count += 1;
            root->left = addNode(root->left, val);
        }
        else
        {
            root->count += 1;
            root->right = addNode(root->right, val);
        }
        return root;
    }
    int findNum(TreeNode *treeRoot, int k)
    {
        int m = 1;
        if (treeRoot->right)
            m = treeRoot->right->count + 1;
        if (k == m)
            return treeRoot->val;
        if (k < m)
        {
            return findNum(treeRoot->right, k);
        }
        else
        {
            return findNum(treeRoot->left, k - m);
        }
    }

    KthLargest(int k, vector<int> &nums) : K(k), root(NULL)
    {
        for (auto i : nums)
        {
            root = addNode(root, i);
        }
    }

    int add(int val)
    {
        root = addNode(root, val);
        return findNum(root, K);
    }
};
