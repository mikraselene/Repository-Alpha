#include <iostream>
#include <list>
#include <map>
#include <set>
#include <vector>

using namespace std;
typedef int NodeID;

#define ASSERT_VALID_MATRIX(mat, mat_size) \
    bool assert_flag = true;               \
    for (auto i : mat)                     \
    {                                      \
        if (i.size() != mat_size)          \
        {                                  \
            assert_flag = false;           \
            break;                         \
        }                                  \
    }                                      \
    assert(assert_flag);

#define ASSERT_VALID_LIST(lst, lst_size) \
    bool assert_flag = true;             \
    for (auto i : lst)                   \
    {                                    \
        if (i.size() >= lst_size)        \
        {                                \
            assert_flag = false;         \
            break;                       \
        }                                \
    }                                    \
    assert(assert_flag);

template <typename T>
struct Node;

template <typename T>
struct Edge
{
    int weight;
    Node<T> *from;
    Node<T> *to;
    Edge(int weight_, Node<T> *from_, Node<T> *to_)
    {
        weight = weight_;
        from = from_;
        to = to_;
    }
};

template <typename T>
struct Node
{
    T data;
    int in;
    int out;
    list<Node<T> *> nexts;
    list<Edge<T> *> edges;
};

template <class T>
class Graph
{

public:
    Graph(vector<vector<int>> adjacency_matrix)
    {
        int size = adjacency_matrix.size();
        ASSERT_VALID_MATRIX(adjacency_matrix, size);
        for (NodeID i = 0; i < size; i++)
        {
            nodes[i] = new Node<T>;
        }
        for (NodeID i = 0; i < size; i++)
        {
            nodes[i]->data = i;
            for (NodeID j = 0; j < size; j++)
            {
                if (adjacency_matrix[i][j] != 0)
                {
                    nodes[i]->nexts.push_back(nodes[j]);
                }
            }
        }
        for (NodeID i = 0; i < size; i++)
        {
            cout << nodes[i]->data << ": ";
            for (auto j : nodes[i]->nexts)
            {
                cout << j->data << " ";
            }
            cout << endl;
        }
    }
    Graph(list<list<NodeID>> adjacency_list)
    {
        int size = adjacency_list.size();
        ASSERT_VALID_LIST(adjacency_list, size);
        for (NodeID i = 0; i < size; i++)
        {
            nodes[i] = new Node<T>;
        }
        NodeID c = 0;
        for (auto item : adjacency_list)
        {
            nodes[c]->data = c;
            for (auto subit : item)
            {
                nodes[c]->nexts.push_back(nodes[subit]);
            }
            c++;
        }
        for (NodeID i = 0; i < size; i++)
        {
            cout << nodes[i]->data << ": ";
            for (auto j : nodes[i]->nexts)
            {
                cout << j->data << " ";
            }
            cout << endl;
        }
    }
    void AddEdge(Edge<T> edge)
    {
        edges.insert(edge);
    }
    bool IsValid()
    {
    }

private:
    map<NodeID, Node<T> *> nodes;
    set<Edge<T> *> edges;
};

int main()
{
    vector<vector<int>> mat = {
        {0, 1, 1, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0},
        {0, 1, 0, 0, 1},
        {1, 0, 0, 0, 0},
    };
    list<list<NodeID>> lst = {
        {1, 4},
        {0, 4, 2, 3},
        {1, 3},
        {1, 4, 2},
        {3, 0, 1},
    };
    Graph<int> G(lst);
}
