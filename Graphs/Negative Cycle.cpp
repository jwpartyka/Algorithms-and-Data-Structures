// Checks using Bellman - Ford whether there's a negative cycle accesible from the source vertex
// If you want to find an arbitrary negative cycle then run negCycle with src = 0
// In case of a negative cycle a vector with indices of edges from a cycle is returned
// If there's no negative cycle then dist[] contains distances of shortest paths from src to every other vertex
// Complexity: O(|V| * |E|)

#define st first
#define nd second

using ll = long long;

const int MAXN = 5e3+5;
const ll INF = 1e18;

struct edge
{
    int v, u, w, id;
};

ll dist[MAXN];
bool vis[MAXN];
pair<int, int> p[MAXN]; // Predecessors (vertex, id of an edge)
vector<edge> E; // List of edges (v, u, w, id)

vector<pair<int, int>> negCycle(int src, int n)
{
    for (int i = 1; i <= n; i++)
    {
        dist[i] = INF;
    }
    dist[src] = 0;

    vector<pair<int, int>> cycle;
    for (int i = 1; i <= n; i++)
    {
        for (auto e : E)
        {
            int v = e.v, u = e.u, w = e.w;
            if (dist[u] > dist[v] + w)
            {
                dist[u] = dist[v] + w;
                p[u] = {v, e.id};

                if (i == n)
                {
                    while (!vis[v])
                    {
                        vis[v] = 1;
                        cycle.push_back(p[v]);
                        v = p[v].st;
                    }
                    reverse(cycle.begin(), cycle.end());
                    while (cycle.back() != p[v])
                    {
                        cycle.pop_back();
                    }
                    break;
                }
            }
        }
    }

    return cycle;
}
