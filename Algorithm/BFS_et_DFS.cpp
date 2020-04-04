#include <iostream>
using namespace std;
#define N 7
int lo = 0, hi = 0;
int queue[N];
bool visited[N] = {0};
bool egde[N][N] = {{0, 0, 1, 1, 0, 1, 0},
                   {0, 0, 1, 0, 0, 0, 0},
                   {1, 1, 0, 1, 0, 0, 0},
                   {1, 0, 1, 0, 0, 0, 0},
                   {0, 0, 0, 0, 0, 0, 1},
                   {1, 0, 0, 0, 0, 0, 1},
                   {0, 0, 0, 0, 1, 1, 0}};
char nodeName[N] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
void BFS(int i)
{
    queue[hi++] = i;
    printf("%c", nodeName[i]);
    visited[i] = 1;
    while (lo != hi)
    {
        int t = queue[lo++];
        for (int j = 0; j < N; j++)
        {
            if (egde[j][t] && !visited[j])
            {
                queue[hi++] = j;
                printf("%c", nodeName[j]);
                visited[j] = 1;
            }
        }
    }
}
void DFS(int i)
{
    printf("%c", nodeName[i]);
    visited[i] = 1;
    for (int j = 0; j < N; j++)
    {
        if (egde[i][j] && !visited[j])
        {
            DFS(j);
        }
    }
}
int main()
{
    memset(visited, 0, N);
    printf("BFS: ");
    for (int i = 0; i < N; i++)
    {
        if (!visited[i])
        {
            BFS(i);
        }
    }
    printf("\n");
    memset(visited, 0, N);
    printf("DFS: ");
    for (int i = 0; i < N; i++)
    {
        if (!visited[i])
        {

            DFS(i);
        }
    }
    printf("\n");
}
