#include <iostream>
using namespace std;
struct Node
{
    int num;
    Node *left, *right;
};
class BST
{
public:
    Node *root;
    BST()
    {
        root = NULL;
    }
    void insert(Node *&root, int n)
    {
        if (root == NULL)
        {
            root = new Node;
            root->num = n;
            root->left = NULL;
            root->right = NULL;
        }
        else if (n < root->num)
        {
            insert(root->left, n);
        }
        else if (n > root->num)
        {
            insert(root->right, n);
        }
    }
    void preorder(Node *root)
    {
        if (!root)
            return;
        cout << root->num << " ";
        preorder(root->left);
        preorder(root->right);
    }
};
int main()
{
    while (1)
    {
        BST bst;
        for (int i = 0; i < 9; ++i)
        {
            int n;
            cin >> n;
            bst.insert(bst.root, n);
        }
        bst.preorder(bst.root);
    }
}