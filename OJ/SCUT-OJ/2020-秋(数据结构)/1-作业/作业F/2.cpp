#include <iostream>
#include <vector>
#include <climits>
using namespace std;

#define INF INT_MAX

struct Edge
{
    int destination;
    int weight;
    Edge()
    {
        destination = INF;
        weight = INF;
    }
    Edge(int d, int w)
    {
        destination = d;
        weight = w;
    }
};
class Graph
{
private:
    int n;
    int c;
    vector<Edge> *vec;
    bool *visited;

public:
    Graph(int n, int c)
    {
        this->n = n;
        this->c = c;
        vec = new vector<Edge>[n];
        visited = new bool[n];
        fill(visited, visited + n, false);
    }
    void Insert(int start, int destination, int weight)
    {
        vec[start - 1].push_back(Edge(destination, weight));
    }

    void Dijkstra(int D[], int s)
    {
        fill(D, D + n, INF);
        D[s - 1] = 0;
        for (int i = 0; i < n; i++)
        {
            int v = Min(D);
            visited[v] = true;
            for (auto elem : vec[v])
            {
                int w = elem.destination - 1;
                if (D[w] > (D[v] + elem.weight))
                {
                    D[w] = (D[v] + elem.weight);
                }
            }
        }
    }
    int Min(int D[])
    {
        int min = INF;
        int v = 0;
        for (int i = 0; i < n; i++)
        {
            if (visited[i] == false && D[i] < min)
            {
                v = i;
                min = D[i];
            }
        }
        return v;
    }
};

int main()
{
    int n, c, s, t;
    cin >> n >> c >> s >> t;
    Graph G(n, c);
    int D[n];
    while (c--)
    {
        int start, destination, weight;
        cin >> start >> destination >> weight;
        G.Insert(start, destination, weight);
        G.Insert(destination, start, weight);
    }
    G.Dijkstra(D, s);
    cout << D[t - 1] << endl;
    return 0;
}

/*
7 11 5 4
2 4 2
1 4 3
7 2 2
3 4 3
5 7 5
7 3 3
6 1 1
6 3 4
2 4 3
5 6 3
7 2 1
*/
