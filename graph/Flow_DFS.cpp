//Najwolniejsze, ale proste znajdywanie maksymalnego przepływu
//Złożoność: O(maxflow * (|V| + |E|))

using ll = long long;

#define st first
#define nd second

const int MAXN = 205, inf = 1e9;

//Przepustowości krawędzi, tablica odwiedzonoych, ujście, id do addEdge, licznik do vis
int E[MAXN*MAXN], vis[MAXN], t, id, tim = 1;
vector<pair<int, int>> G[MAXN]; //Graf

//Krawędź (a, b) o przepustowości c
void addEdge(int a, int b, int c)
{
    G[a].push_back({b, id});
    E[id++] = c;
    G[b].push_back({a, id++});
}

int dfs(int v, int flow)
{
    if (v == t) //Jesteś w ujściu
    {
        return flow;
    }
    vis[v] = tim;
    for (auto e : G[v])
    {
        int u = e.st, x = e.nd;
        int f = E[x];
        if (vis[u] == tim) continue;
        if (f) f = dfs(u, min(flow, f));
        if (f) //(v, u) należy do ścieżki powiększającej
        {
            E[x] -= f;
            E[x^1] += f;
            return f;
        }
    }
    return 0; //Nie znaleziono ścieżki powiększającej
}

ll maxflow(int src)
{
    ll flow = 0;
    while (int f = dfs(src, inf))
    {
        flow += f;
        tim++;
    }
    return flow;
}
