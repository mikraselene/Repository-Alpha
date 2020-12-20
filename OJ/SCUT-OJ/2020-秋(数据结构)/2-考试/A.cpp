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
    void DFS(int start)
    {
        function<void(int)> dfs = [&](int j) {
            visited[j] = true;
            for (int i = start; i < nodes; i++)
            {
                if (adj_mat[i][j] && !visited[i])
                {
                    dfs(i);
                }
            }
        };
        if (!visited[start])
        {
            dfs(start);
        }
    }
    int Count()
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
        return cnt;
    }

    bool adj_mat[N_MAX][N_MAX];

private:
    bool visited[N_MAX];
    int nodes;
};

int main()
{
    int n;
    cin >> n;
    Graph *G = new Graph(n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int k;
            cin >> k;
            G->adj_mat[i][j] = k ? true : false;
        }
    }
    cout << G->Count() << endl;
    delete G;
}
