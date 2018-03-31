// Ford - Fulkerson method
//Złożoność: O(maxflow * (|V| + |E|))
// Usage: [SPOJ] FLOW http://www.spoj.com/A12/problems/FLOW/
//        [VI POI] Speleology https://szkopul.edu.pl/problemset/problem/l7RiYCdarLZV51E2daTt4n4W/site/?key=statement

#define st first
#define nd second

const int MAXN = 205, INF = 1e9;

// Capacities, visited vertices, id of the target
int E[MAXN*MAXN], vis[MAXN], t, id, tim = 1;
vector<pair<int, int>> G[MAXN]; // Graph

// Adds edge (a, b) with capacity c and its opposite edge
void addEdge(int a, int b, int c)
{
    G[a].push_back({b, id});
    E[id++] = c;
    G[b].push_back({a, id++});
}

int dfs(int v, int flow)
{
    if (v == t)
    {
        // You've reached the target = found an augmenting path
        return flow;
    }
    vis[v] = tim;
    for (auto e : G[v])
    {
        int u = e.st, x = e.nd;
        if (vis[u] == tim) continue;
        int w = E[x], f = 0;
        if (w) f = dfs(u, min(flow, w));
        if (f)
        {
            E[x] -= f;
            E[x^1] += f;
            return f;
        }
    }
    return 0; // There aren't any augmenting paths in the graph
}

long long maxflow(int src)
{
    long long flow = 0;
    while (int f = dfs(src, INF))
    {
        flow += f;
        tim++;
    }
    return flow;
}
