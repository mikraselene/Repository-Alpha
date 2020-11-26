#include <iostream>
#include <cstring>
using namespace std;
int main()
{
    int m, n, c;
    cin >> m;
    while (m--)
    {
        int s, t;
        cin >> n >> c;
        bool graph[n][n];
        memset(graph, false, sizeof(graph));
        while (c--)
        {
            cin >> s >> t;
            graph[s - 1][t - 1] = true;
        }
        int max = 0;
        for (int i = 0; i < n; i++)
        {
            int count = 0;
            for (int j = 0; j < n; j++)
            {
                if (graph[j][i] == true)
                {
                    count++;
                }
            }
            if (count > max)
            {
                max = count;
            }
        }
        cout << max << endl;
    }
}
