#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
#define N_MAX 200

class Graph
{
public:
    Graph(int nodes, int start)
    {
        this->nodes = nodes;
        this->start = start;
        memset(adj_mat, false, sizeof(adj_mat));
        memset(visited, false, sizeof(visited));
    }
    void AddEdge(int i, int j)
    {
        adj_mat[i][j] = true;
        adj_mat[j][i] = true;
    }
    void DFS()
    {
        function<void(int)> dfs = [&](int j) {
            cout << (j != start ? " " : "") << j;
            visited[j] = true;
            for (int i = start; i < nodes; i++)
            {
                if (adj_mat[i][j] && !visited[i])
                {
                    dfs(i);
                }
            }
        };
        for (int i = start; i < nodes; i++)
        {
            if (!visited[i])
            {
                dfs(i);
            }
        }
    }
    void BFS()
    {
        queue<int> q;
        for (int i = start; i < nodes; i++)
        {
            if (!visited[i])
            {
                visited[i] = true;
                cout << (i != start ? " " : "") << i;
                q.push(i);
                while (!q.empty())
                {
                    i = q.front();
                    q.pop();
                    for (int j = start; j < nodes; j++)
                    {
                        if (adj_mat[i][j] && !visited[j])
                        {
                            visited[j] = true;
                            cout << (j != start ? " " : "") << j;
                            q.push(j);
                        }
                    }
                }
            }
        }
    }

private:
    bool adj_mat[N_MAX][N_MAX];
    bool visited[N_MAX];
    int nodes;
    int start;
};

int main()
{
    int k;
    cin >> k;
    while (k--)
    {
        int n, e, s;
        cin >> n >> e >> s;
        Graph G(n, s);
        while (e--)
        {
            int i, j;
            cin >> i >> j;
            G.AddEdge(i, j);
        }
        G.DFS();
    }
}
