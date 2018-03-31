// Johnson's algorithm for computing distances between every pair of vertices
// Uses SPFA to get rid of negative weight
// Returns 0 in case of a negative cycle
// Complexity: O(|V|*|E|*log|V| + |V|*|E|)
// Usage: [SPOJ] JHNSN http://www.spoj.com/problems/JHNSN/

#define st first
#define nd second

const int MAXN = 2e3+5, inf = 1e9;

int dist[MAXN][MAXN], h[MAXN], relax[MAXN]; // Distances, values for reweighting
bool used[MAXN]; // used[v] = is vertex v on the queue
vector<pair<int, int>> G[MAXN]; // Graph
priority_queue<pair<int, int>> PQ; // Priority queue for Dijkstra
queue<int> Q; // Queue for SPFA

bool SPFA(int src, int n)
{
    for (int i = 1; i <= n; i++) h[i] = INF;
    h[src] = 0;
    Q.push(src);
    while (!Q.empty())
    {
        int v = Q.front();
        Q.pop();
        used[v] = 0, relax[v]++;
        // If a path to vertex v was relaxed n times then there is a negative cycle
        if (relax[v] == n) return 0;
        for (auto e : G[v])
        {
            int u = e.st, w = e.nd;
            if (h[u] > h[v] + w)
            {
                h[u] = h[v] + w;
                if (used[u]) continue;
                used[u] = 1;
                Q.push(u);
            }
        }
    }
    return 1;
}

void dijkstra(int src, int n)
{
    for (int i = 1; i <= n; i++) dist[src][i] = INF;
    dist[src][src] = 0;
    PQ.push({0, src});
    while (!PQ.empty())
    {
        int v = PQ.top().nd, ww = PQ.top().st;
        PQ.pop();
        if (dist[src][v] > ww) continue;
        for (auto e : G[v])
        {
            int u = e.st, w = e.nd + h[v] - h[u];
            if (dist[src][u] > dist[src][v] + w)
            {
                dist[src][u] = dist[src][v] + w;
                PQ.push({-dist[src][u], u});
            }
        }
    }
}

bool johnson(int n)
{
    // Adds an imaginary vertex from which SPFA will be run
    for (int i = 1; i <= n; i++) G[0].push_back({i, 0});
    if (SPFA(0, n)) // Reweights edges, detects a negative cycle
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
