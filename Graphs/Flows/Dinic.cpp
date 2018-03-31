// Computes maxflow using Dinic's algorithm.
// Complexity:
// 1) In a random graph: O(|V|^2 * |E|)
// 2) In graphs with unit distances: O(min{ |V|^(2/3), |E|^(1/2) } * |E|)
// 3) In barpitite graphs: O(|E| * |V|^(1/2)))
// Usage: [SPOJ] FASTFLOW http://www.spoj.com/problems/FASTFLOW/
//        [VI POI] Speleology https://szkopul.edu.pl/problemset/problem/l7RiYCdarLZV51E2daTt4n4W/site/?key=statement
//        [XVIII POI] Programming Contest https://szkopul.edu.pl/problemset/problem/VwDLJhYqi1z_sZrb2NyfvQ5e/site/?key=statement
//        [XVII POI] Bridges https://szkopul.edu.pl/problemset/problem/gh2Yj6Ckrt4Lo_RojONuljuC/site/?key=statement

#define st first
#define nd second

using ll = long long;

const int MAXN = 5e3 + 5, inf = 1e9;

// Capacities, distance in BFS, number of vertices, id of the target
int E[MAXN*MAXN], dist[MAXN], n, t, id;
vector<pair<int, int>> G[MAXN], GL[MAXN]; // Graph, Level graph

// Adds edge (a, b) with capacity c and its opposite edge
void addEdge(int a, int b, int c)
{
    G[a].push_back({b, id});
    E[id++] = c;
    G[b].push_back({a, id++});
}

// Builds the level graph
bool bfs(int src)
{
    // Resetting the distances and clearing the graph
    for (int i = 0; i <= n; i++)
    {
        dist[i] = 0;
        GL[i].clear();
    }

    queue<int> Q;
    Q.push(src);
    dist[src] = 1;

    while (!Q.empty())
    {
        int v = Q.front();
        Q.pop();

        for (auto e : G[v])
        {
            int u = e.st, x = e.nd;

            // If visited and positive capacity
            if (!dist[u] && E[x])
            {
                dist[u] = dist[v] + 1;
                Q.push(u);
            }

            // If edge(v, u) leads from one level to the next one
            if (dist[u] == dist[v] + 1)
            {
                GL[v].push_back({u, x});
            }
        }
    }

    return dist[t]; // If an augmenting path exists return 1
}

int dfs(int v, int flow)
{
    if (v == t)
    {
        // You've reached the target = found an augmenting path
        return flow;
    }

    for (int i = 0; i < GL[v].size(); i++)
    {
        auto e = GL[v][i];
        int u = e.st, x = e.nd;

        int f = E[x];
        if (f) f = dfs(u, min(flow, f));
        if (!f) // Edge (v, u) does NOT belong to any augmenting path
        {
            // Delete the edge
            swap(GL[v][i], GL[v].back());
            GL[v].pop_back();
            i--;
            continue;
        }

        // Edge (v, u) belongs to some augmenting path
        E[x] -= f;
        E[x ^ 1] += f; // ID of the edge opposite to x is (x ^ 1)
        return f;
    }

    return 0; // There aren't any augmenting paths in the level graph
}

ll dinic(int src)
{
    ll flow = 0;
    while (bfs(src)) // While there's an augmenting path in the graph
    {
        while (int f = dfs(src, inf)) // While there's an augmenting path in the level graph
        {
            flow += f;
        }
    }
    return flow;
}
