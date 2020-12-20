#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

#define N_MAX 500

class Graph
{
public:
    Graph(int n)
    {
        nodes = n;
        memset(adj_mat, false, sizeof(adj_mat));
        memset(visited, false, sizeof(visited));
    }
    void AddEdge(int i, int j)
    {
        adj_mat[i - 1][i - 1] = true;
        adj_mat[i - 1][j - 1] = true;
        adj_mat[j - 1][i - 1] = true;
    }
    void BFS(int start)
    {
        queue<int> q;
        q.push(start);
        visited[start] = true;
        while (!q.empty())
        {
            int j = q.front();
            q.pop();
            for (int i = 0; i < nodes; i++)
            {
                if (!visited[i] && adj_mat[j][i])
                {
                    visited[i] = true;
                    q.push(i);
                }
            }
        }
    }
    bool Func()
    {
        int cnt = 0;
        for (int i = 0; i < nodes; i++)
        {
            if (!visited[i])
            {
                BFS(i);
                cnt++;
            }
        }
        return cnt == 1 ? true : false;
    }

private:
    bool adj_mat[N_MAX][N_MAX];
    bool visited[N_MAX];
    int nodes;
};

int main()
{
    int k;
    cin >> k;
    while (k--)
    {
        int n, e;
        cin >> n >> e;
        Graph G(n);
        while (e--)
        {
            int i, j;
            cin >> i >> j;
            G.AddEdge(i, j);
        }
        cout << (G.Func() ? "YES" : "NO") << endl;
    }
}
