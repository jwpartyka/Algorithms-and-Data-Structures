//Znajdywanie maksymalnego przepływu
//Lepiej podpiąć źródło do super-źródła: addEdge(super-źródło, źródło, INF), maxflow(super-źródło)
//Złożoność: O(|V| * |E|^2)

#define st first
#define nd second

const int MAXN = 205, INF = 1e9;

//Przepustowości krawędzi, tablica odwiedzonoych, ujście, id do addEdge, licznik do vis
int E[MAXN*MAXN], vis[MAXN], t, id, tim;
pair<int, int> p[MAXN]; //Tablica poprzedników w BFS
vector<pair<int, int>> G[MAXN]; //Graf

//Krawędź (a, b) o przepustowości c
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
                    //Jesteś w ujściu - znaleziono ścieżkę powiększającą
                    return flow;
                }
                Q.push({u, flow});
            }
        }
    }
    return 0; //Nie znaleziono ścieżki powiększającej
}

long long maxflow(int src)
{
    long long flow = 0;
    while (int f = bfs(src))
    {
        flow += f;
        //Aktualizacja przepustowości:
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
