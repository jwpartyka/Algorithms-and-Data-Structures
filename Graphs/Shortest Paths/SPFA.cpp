// Computes shortest paths from the source to every other vertex
// Returns 0 in case of a negative cycle
// On graphs with positive weight only it's better to use Dijkstra
// Usually runs faster than Bellman - Ford but worst - case complexity is the same
// It's useful in mincost
// Usage: [SPOJ] NEGCYC http://www.spoj.com/problems/NEGCYC/

#define st first
#define nd second

const int MAXN = 5e5+5, INF = 1e9;
int dist[MAXN]; // Distances from the source
vector<pair<int, int>> G[MAXN]; // Graph
queue<pair<int, int>> Q; // Queue for SPFA
int relax[MAXN]; // relax[v] = how many times has a path to v been relaxed

bool SPFA(int start, int n)
{
    for (int i = 1; i <= n; i++) dist[i] = INF;
    dist[start] = 0;
    Q.push({0, start});
    while(!Q.empty())
    {
        int v = Q.front().nd;
        int ww = Q.front().st;
        Q.pop();
        if (dist[v] < ww) continue;
        for (auto e : G[v])
        {
            int u = e.st, w = e.nd;
            if (dist[u] > dist[v] + w)
            {
                relax[u]++;
                // If a path to vertex v was relaxed n times then there is a negative cycle
                if (relax[u] == n) return 0;
                dist[u] = dist[v] + w;
                Q.push({dist[u], u});
            }
        }
    }
    return 1;
}
