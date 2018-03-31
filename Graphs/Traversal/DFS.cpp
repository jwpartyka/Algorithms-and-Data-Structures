// Computes depths of vertices and sizes of subtrees
// Complexity: O(|V| + |E|)

const int MAXN = 1e6+5;

int sz[MAXN], d[MAXN]; // Sizes of subtrees, depths of vertices
vector<int> G[MAXN]; // Graph

void dfs(int v, int p)
{
    sz[v] = 1;
    for (int u : G[v])
    {
        if (u == p) continue;
        d[u] = d[v] + 1;
        dfs(u, v);
        sz[v] += sz[u];
    }
}
