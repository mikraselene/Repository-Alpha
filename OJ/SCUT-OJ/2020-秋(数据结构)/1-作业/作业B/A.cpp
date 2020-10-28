#include <iostream>
#include <queue>

using namespace std;

struct node
{
    char data;
    node *left, *right;
};

string s;
int i = 0;
queue<node *> q;

node *Create()
{
    node *T;
    char c;
    c = s[i++];
    if (c >= 'A' && c <= 'Z')
    {
        T = new node;
        T->data = c;
        T->left = NULL;
        T->right = NULL;
    }
    else
    {
        T = new node;
        T->data = c;
        T->left = Create();
        T->right = Create();
    }
    return T;
}

void Print(node *T)
{
    q.push(T);
    int k = 0;
    while (!q.empty() && k++ < 100)
    {
        T = q.front();
        q.pop();
        cout << T->data;
        if (T->left)
        {
            q.push(T->left);
        }
        if (T->right)
        {
            q.push(T->right);
        }
    }
}

int main()
{
    node *root;
    int n;
    cin >> n;
    while (n--)
    {
        cin >> s;
        i = 0;
        root = Create();

        Print(root);
        cout << endl;
    }
}