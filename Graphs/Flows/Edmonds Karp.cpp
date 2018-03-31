// Computes maxflow using Edmonds - Karp algorithm
// Complexity: O(|V| * |E|^2)
// Usage: [SPOJ] FLOW http://www.spoj.com/A12/problems/FLOW/
//        [VI POI] Speleology https://szkopul.edu.pl/problemset/problem/l7RiYCdarLZV51E2daTt4n4W/site/?key=statement
//        [XVIII POI] Programming Contest https://szkopul.edu.pl/problemset/problem/VwDLJhYqi1z_sZrb2NyfvQ5e/site/?key=statement
//        [XVII POI] Bridges https://szkopul.edu.pl/problemset/problem/gh2Yj6Ckrt4Lo_RojONuljuC/site/?key=statement

#define st first
#define nd second

const int MAXN = 205, INF = 1e9;

// Capacities, visited vertices, id of the target
int E[MAXN*MAXN], vis[MAXN], t, id, tim;
pair<int, int> p[MAXN]; // Predecessors in BFS
vector<pair<int, int>> G[MAXN]; // Graph

// Adds edge (a, b) with capacity c and its opposite edge
void addEdge(int a, int b, int c)
{
    G[a].push_back({b, id});
    E[id++] = c;
    G[b].push_back({a, id++});
}

int bfs(int src)
{
    queue<pair<int, int>> Q;
    vis[src] = ++tim;
    Q.push({src, INF});
    while (!Q.empty())
    {
        int v = Q.front().st, flow = Q.front().nd;
        Q.pop();
        for (auto e : G[v])
        {
            int u = e.st, x = e.nd;
            if (vis[u] == tim) continue;
            int w = E[x];
            if (w > 0)
            {
                flow = min(flow, w);
                vis[u] = tim;
                p[u] = {v, x};
                if (u == t)
                {
                    // You've reached the target = found an augmenting path
                    return flow;
                }
                Q.push({u, flow});
            }
        }
    }
    return 0; // There aren't any augmenting paths in the graph
}

long long maxflow(int src)
{
    long long flow = 0;
    while (int f = bfs(src))
    {
        flow += f;
        // Updates capacities
        int cur = t;
        while (cur)
        {
            int x = p[cur].nd;
            E[x] -= f;
            E[x^1] += f;
            cur = p[cur].st;
        }
    }
    return flow;
}
