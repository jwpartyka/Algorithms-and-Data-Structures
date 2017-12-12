//Najwolniejsze, ale proste znajdywanie maksymalnego przepływu
//Złożoność: O(maxflow * (|V| + |E|))

#define st first
#define nd second

const int MAXN = 205, INF = 1e9;

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
    if (!flow || v == t)
    {
        //Przeszedłeś zapchaną krawędzią lub dotarłeś do ujścia
        return flow;
    }
    vis[v] = tim;
    for (auto e : G[v])
    {
        int u = e.st, x = e.nd;
        int w = E[x];
        if (vis[u] == tim) continue;
        int f = dfs(u, min(flow, w));
        if (f) //(v, u) należy do ścieżki powiększającej
        {
            E[x] -= f;
            E[x^1] += f;
            return f;
        }
    }
    return 0; //Nie znaleziono ścieżki powiększającej
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
