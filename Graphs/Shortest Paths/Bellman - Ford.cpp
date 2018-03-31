// Computes shortest paths from the source to every other vertex
// Returns 0 in case of a negative cycle
// Complexity: O(|V| * |E|)
// Usage: [SPOJ] NEGCYC http://www.spoj.com/problems/NEGCYC/

const int MAXN = 1e4+5, INF = 1e9;
int dist[MAXN]; // Distances from the source
vector<pair<pair<int, int>, int>> E; // Edge (v, u) with weight w

bool relax()
{
    bool ok = 1;
    for (auto e : E)
    {
        int v = e.st.st, u = e.st.nd, w = e.nd;
        if (dist[u] > dist[v] + w)
        {
            ok = 0;
            dist[u] = dist[v] + w;
        }
    }
    return ok;
}
bool bellman_ford(int start, int n)
{
    for (int i = 1; i < MAXN; i++) dist[i] = INF;
    dist[start] = 0;
    for (int i = 1; i < n; i++)
    {
        relax();
    }
    return relax();
}
