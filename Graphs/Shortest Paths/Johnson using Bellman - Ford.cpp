// Johnson's algorithm for computing distances between every pair of vertices
// Uses Bellman - Ford to get rid of negative weight
// Returns 0 in case of a negative cycle
// Complexity: O(|V|*|E|*log|V| + |V|*|E|)
// Usage: [SPOJ] JHNSN http://www.spoj.com/problems/JHNSN/

#define st first
#define nd second

const int MAXN = 2e3+5, inf = 1e9;

struct edge
{
    int v, u, w;
};

int dist[MAXN][MAXN], h[MAXN]; // Distances, values for reweighting
vector<pair<int, int>> G[MAXN]; // Graph
vector<edge> E; // List of edges for Bellman - Ford
priority_queue<pair<int, int>> Q; // Priority queue for Dijkstra

bool bellman_ford(int n)
{
    for (int i = 1; i <= n; i++)
    {
        for (auto e : E)
        {
            int v = e.v, u = e.u, w = e.w;
            if (h[u] > h[v] + w)
            {
                if (i == n) return 0; // There is a negative cycle
                h[u] = h[v] + w;
            }
        }
    }
    return 1;
}

void dijkstra(int src, int n)
{
    for (int i = 1; i <= n; i++) dist[src][i] = inf;

    dist[src][src] = 0;
    Q.push({0, src});

    while (!Q.empty())
    {
        int v = Q.top().nd, w = Q.top().st;
        Q.pop();
        if (dist[src][v] > w) continue;

        for (auto e : G[v])
        {
            int u = e.st, w = e.nd + h[v] - h[u];
            if (dist[src][u] > dist[src][v] + w)
            {
                dist[src][u] = dist[src][v] + w;
                Q.push({-dist[src][u], u});
            }
        }
    }
}

bool johnson(int n)
{
    if (bellman_ford(n)) // Reweights edges, detects a negative cycle
    {
        for (int i = 1; i <= n; i++)
        {
            // Computes distances from i to every other vertex
            dijkstra(i, n);
        }
        return 1;
    }
    return 0;
}
