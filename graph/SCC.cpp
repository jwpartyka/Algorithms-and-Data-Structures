//Dzieli graf na silnie spójne składowe
//Tworzy graf transponowany na którym znajduje numery postorder,
//a następnie rozważa wierzchołki z oryginalnego grafu w kolejności
//odwróconego postorder
//Złożoność: O(|V|)

const int MAXN = 1e4+5;

int SCC[MAXN], nr; //SCC[i] - w której silnie spójnej jest i-ty wierzchołek
bool vis[MAXN]; //Tablica odwiedzonych
//Graf, graf transponowany, graf silnie spójnych
vector<int> G[MAXN], Gt[MAXN], Gscc[MAXN];
stack<int> S; //Stos trzymający odwróconą numerację postorder

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
    //Dodaje krawędź do oryginalnego grafu:
    G[a].push_back(b);
    //Dodaje krawędź do transponowanego grafu:
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
