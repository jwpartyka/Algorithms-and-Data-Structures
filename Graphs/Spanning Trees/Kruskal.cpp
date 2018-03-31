// Kruskal's algorithm for finding MST
// It uses FU
// Complexity O(|E| * log |E|)
// Usage: [SPOJ] MST http://www.spoj.com/problems/MST/

const int MAXN = 5e5+5;
struct edge
{
    int v, u, w;
};
bool cmp(edge a, edge b)
{
    return a.w < b.w;
}
vector<edge> E; // List of edges (v, u) with weight w
vector<pair<int, int>> MST[MAXN];

void findMST(int n)
{
    for (int i = 1; i <= n; i++)
    {
        initSet(i);
    }
    sort(E.begin(), E.end(), cmp);
    for (auto e : E)
    {
        int v = FIND(e.v), u = FIND(e.u);
        if (v == u) continue;
        UNION(v, u);
        MST[v].push_back({u, e.w});
        MST[u].push_back({v, e.w});
    }
}
