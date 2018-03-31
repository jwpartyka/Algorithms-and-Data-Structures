// Divides a graph into strongly connected components using Kosaraju's algorithm.
// 1) Creates a transpose graph and computes postorder numbers of each vertex
// 2) Processes vertices of the original graph in reverse postorder from 1)
// Complexity: O(|V| + |E|)
// Usage: [III POI] Agents https://szkopul.edu.pl/problemset/problem/lLzgarYSJUxLS5UXJHeyHl7U/site/?key=statement
// Usage: [XIII POI] Professor Szu https://szkopul.edu.pl/problemset/problem/EijIYL4qkxxGJGHaVVnvdmgY/site/?key=statement

const int MAXN = 1e4+5;

int SCC[MAXN], nr; //SCC[v] - id of the SCC in which vertex v is
bool vis[MAXN]; // Visited vertices
//Graf, graf transponowany, graf sinie spójnych
// Graph, transpose graph, scc graph
vector<int> G[MAXN], Gt[MAXN], Gscc[MAXN];
stack<int> S; // Stack containing reverse postorder

void dfs(int v)
{
    vis[v] = 1;
    for (int u : Gt[v])
    {
        if (!vis[u]) dfs(u);
    }
    S.push(v);
}

void findSCC(int v)
{
    vis[v] = 0, SCC[v] = nr;
    for (int u : G[v])
    {
        if (!vis[u])
        {
            if (SCC[v] != SCC[u])
            {
                Gscc[SCC[v]].push_back(SCC[u]);
            }
            continue;
        }
        calcSCC(u);
    }
}

void addEdge(int a, int b)
{
    // Adds edge to the graph
    G[a].push_back(b);
    // Adds edge to the transpose graph
    Gt[b].push_back(a);
}

void sccBuild(n)
{
    for (int i = 1; i <= n; i++)
    {
        if (!vis[i]) dfs(i);
    }
    while (!S.empty())
    {
        int v = S.top();
        S.pop();
        if (vis[v])
        {
            calcSCC(v);
            nr++;
        }
    }
}
