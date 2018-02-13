//Znajdywanie maksymalnego przepływu
//Złożoność O(|V|^2 * |E|), dla grafów z krawędziami jednostkowymi O(|E| * SQRT(|V|))

using ll = long long;

#define st first
#define nd second

const int MAXN = 5e3+5, inf = 1e9;

//Przepustowości krawędzi, odległości, liczba wierzchołków, ujście, id do addEdge
int E[MAXN*MAXN], dist[MAXN], n, t, id;
vector<pair<int, int>> G[MAXN], GL[MAXN]; //Graf, Graf BFS

//Krawędź (a, b) o przepustowości c
inline void addEdge(int a, int b, int c)
{
    G[a].push_back({b, id});
    E[id++] = c;
    G[b].push_back({a, id++});
}

bool bfs(int src)
{
    for (int i = 1; i <= n; i++)
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
            if (!dist[u] && E[x])
            {
                dist[u] = dist[v] + 1;
                Q.push(u);
            }
            if (dist[u] == dist[v] + 1) //(v, u) jest na najkrótszej ścieżce (src, u)
            {
                //Dodaj (v, u) do grafu BFS
                GL[v].push_back({u, x});
            }
        }
    }
    return dist[t]; //Czy istnieje ścieżka powiększająca
}

int dfs(int v, int flow)
{
    if (v == t)
    {
        //Przeszedłeś zapchaną krawędzią lub dotarłeś do ujścia
        return flow;
    }
    for (int i = 0; i < GL[v].size(); i++)
    {
        auto e = GL[v][i];
        int u = e.st, x = e.nd;
        int f = E[x];
        if (f) f = dfs(u, min(flow, f));
        if (!f) //(v, u) NIE należy do żadnej ścieżki powiększającej
        {
            //Usuwanie zbędnej krawędzi:
            swap(GL[v][i], GL[v].back());
            GL[v].pop_back();
            i--;
            continue;
        }
        //(v, u) należy do ścieżki powiększającej
        E[x] -= f;
        E[x ^ 1] += f;
        return f;
    }
    return 0; //Nie znaleziono ścieżki powiększającej
}

ll dinic(int src)
{
    ll flow = 0;
    while (bfs(src)) //Dopóki istnieje ścieżka powiększająca w grafie
    {
        while (int f = dfs(src, inf)) //Dopóki istnieje ścieżka powiększająca w grafie BFS
        {
            flow += f;
        }
    }
    return flow;
}
