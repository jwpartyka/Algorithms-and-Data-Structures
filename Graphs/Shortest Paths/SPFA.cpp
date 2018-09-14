// Computes shortest paths from the source to every other vertex
// Returns 0 in case of a negative cycle
// On graphs with positive weight only it's better to use Dijkstra
// Usually runs faster than Bellman-Ford but worst-case complexity is the same
// It's useful in mincost

#define st first
#define nd second

const int MAXN = 1e4 + 5, inf = 1e9 + 5;

int dist[MAXN], cnt[MAXN]; // Distance from the source, cnt[v] = how many times paths to v have been relaxed
vector<pair<int, int>> G[MAXN];

bool SPFA(int src, int n)
{
    for (int i = 1; i <= n; i++)
    {
        dist[i] = inf;
    }
    dist[src] = 0;

    deque<pair<int, int>> Q;
    Q.push_front({src, 0});
    while (!Q.empty())
    {
        int v = Q[0].st, w = Q[0].nd;
        Q.pop_front();
        if (dist[v] < w) continue;

        for (auto e : G[v])
        {
            int u = e.st, w = e.nd;
            if (dist[u] > dist[v] + w)
            {
                dist[u] = dist[v] + w;
                if (dist[u] < Q[0].nd) Q.push_front({u, dist[u]});
                else Q.push_back({u, dist[u]});
                cnt[u]++;
                if (cnt[u] == n) return 0;
            }
        }
    }

    return 1;
}
