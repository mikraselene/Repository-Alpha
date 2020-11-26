#include <iostream>
using namespace std;

struct Node
{
    char data;
    Node *left, *right;
};

string s;
int i = 0;
Node *Create()
{
    Node *T;
    char c;
    c = s[i++];
    if (c >= 'A' && c <= 'Z')
    {
        T = new Node;
        T->data = c;
        T->left = NULL;
        T->right = NULL;
    }
    else
    {
        T = new Node;
        T->data = c;
        T->left = Create();
        T->right = Create();
    }
    return T;
}

int Depth(Node *root)
{
    if (root == NULL)
    {
        return 0;
    }
    int nLeft = Depth(root->left);
    int nRight = Depth(root->right);
    return nLeft > nRight ? nLeft + 1 : nRight + 1;
}

bool IsBalanced(Node *root)
{
    if (root == NULL)
    {
        return true;
    }
    int left = Depth(root->left);
    int right = Depth(root->right);
    int diff = left - right;
    if (diff > 1 || diff < -1)
    {
        return false;
    }
    return IsBalanced(root->left) && IsBalanced(root->right);
}
int main()
{
    Node *root;
    int n;
    cin >> n;
    while (n--)
    {
        cin >> s;
        i = 0;
        root = Create();
        cout << (IsBalanced(root) ? "B" : "N") << endl;
    }
}