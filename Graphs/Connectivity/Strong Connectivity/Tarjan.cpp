// Divides a graph into strongly connected components using Tarjan's algorithm.
// Algorithm runs only one DFS
// Complexity: O(|V| + |E|)
// Usage: [III POI] Agents https://szkopul.edu.pl/problemset/problem/lLzgarYSJUxLS5UXJHeyHl7U/site/?key=statement
// Usage: [XIII POI] Professor Szu https://szkopul.edu.pl/problemset/problem/EijIYL4qkxxGJGHaVVnvdmgY/site/?key=statement

const int MAXN = 1e6 + 5;

int low[MAXN], pre[MAXN], SCC[MAXN], tim = 1, num = 1;
bool used[MAXN];
vector<int> G[MAXN], Gscc[MAXN];
stack<int> St;

void dfs(int v)
{
    low[v] = pre[v] = tim++;
    St.push(v);
    used[v] = 1;
    for (int u : G[v])
    {
        if (low[u])
        {
            if (used[u]) low[v] = min(low[v], pre[u]);
        }
        else
        {
            dfs(u);
            low[v] = min(low[v], low[u]);
        }
    }

    if (low[v] != pre[v]) return ;

    int cur = v;
    do
    {
        v = St.top();
        St.pop();
        used[v] = 0;
        SCC[v] = num;
        for (int u : G[v])
        {
            if (SCC[u] && SCC[v] != SCC[u])
            {
                Gscc[SCC[v]].push_back(SCC[u]);
            }
        }
    }
    while (v != cur);
    num++;
}

void sccBuild(int n)
{
    for (int i = 1; i <= n; i++)
    {
        if (!low[i]) dfs(i);
    }
}
