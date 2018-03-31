// Computes distances between every pair of vertices
// Returns 0 in case of a negative cycle
// Complexity: O(|V|^3)
// Usage: [SPOJ] NEGCYC http://www.spoj.com/problems/NEGCYC/

const int MAXN = 5e2+5, INF = 1e9;
int dist[MAXN][MAXN]; // Distances

bool floyd_warshall(int n)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = i + 1; j <= n; j++)
        {
            // If edge(i, j) existed it would have a non - negative weight
            if (!dist[i][j]) dist[i][j] = INF;
            if (!dist[j][i]) dist[j][i] = INF;
        }
    }

    for (int k = 1; k <= n; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    for (int i = 1; i <= n; i++)
    {
        // If a path from vertex to itself has a negative distance then there exists a negative cycle
        if (dist[i][i] < 0) return 0;
    }
    return 1;
}
