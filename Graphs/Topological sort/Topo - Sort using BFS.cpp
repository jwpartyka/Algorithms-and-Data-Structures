// Topo - sort using BFS
// Graph must be a DAG
// After processing edge (v, u) indeg[u] is decremented
// Adds a vertex to the queue when indeg[u] = 0
// Adds a vertex to the stack after removing it from the queue
// Complexity: O(|V| + |E|)
// Usage: [SPOJ] TOPOSORT http://www.spoj.com/problems/TOPOSORT/

const int MAXN = 1e6+5;

int indeg[MAXN];
bool vis[MAXN];
vector<int> G[MAXN];
stack<int> topo;

void sortuj(int n)
{
    queue<int> Q;
    for (int i = 1; i <= n; i++)
    {
        if (!indeg[i])
        {
            Q.push(i);
        }
    }

    while (!Q.empty())
    {
        int v = Q.front();
        topo.push(v);
        Q.pop();
        for (int u : G[v])
        {
            indeg[u]--;
            if (!indeg[u])
            {
                Q.push(u);
            }
        }
    }
}
