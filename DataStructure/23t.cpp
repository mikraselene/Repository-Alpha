#include <iostream>
using namespace std;

enum NodeState
{
    NIL,
    TWO,
    THREE,
};

template <class T>
struct Node
{
    NodeState state;
    T left_data;
    T right_data;
    Node *left;
    Node *middle;
    Node *right;
    Node(int ldata, Node *l, Node *r)
    {
        state = TWO;
        left_data = ldata;
        left = l;
        right = r;
    }
    Node(int ldata, int rdata, Node *l, Node *m, Node *r)
    {
        state = THREE;
        left_data = ldata;
        right_data = rdata;
        left = l;
        middle = m;
        right = r;
    }
};

template <class T>
class TwoThreeTree
{
    typedef Node<T> *Ptr;

public:
    TwoThreeTree()
    {
        root = NULL;
    }
    ~TwoThreeTree()
    {
        function<void(Ptr)> destroy = [&](Ptr node) {
            if (node != NULL)
            {
                destroy(node->left);
                destroy(node->middle);
                destroy(node->right);
                delete node;
            }
        };
        destroy(root);
    }
    bool Search()
    {
    }
    void Insert()
    {
    }

private:
    Ptr root;
};

int main()
{
    Node<int> A(1, NULL, NULL);
    Node<char> B('a', 'b', NULL, NULL, NULL);
}