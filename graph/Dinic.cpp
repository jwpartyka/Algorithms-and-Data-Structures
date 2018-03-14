//Znajdywanie maksymalnego przepływu algorytmem Dinica
//Złożoność:
//1) W dowolnym grafie: O(|V|^2 * |E|)
//2) W grafach z krawędziami jednostkowymi: O(min{ |V|^(2/3), |E|^(1/2) } * |E|)
//3) W grafach dwudzielnych O(|E| * sqrt(|V|))

#define st first
#define nd second

using ll = long long;

const int MAXN = 5e3 + 5, inf = 1e9;

//Przepustowości krawędzi, odległości BFS, liczba wierzchołków, numer ujścia, id do addEdge
int E[MAXN*MAXN], dist[MAXN], n, t, id;
vector<pair<int, int>> G[MAXN], GL[MAXN]; //Graf, Graf BFS

//Krawędź (a, b) o przepustowości c i krawędź do niej przeciwną:
void addEdge(int a, int b, int c)
{
    G[a].push_back({b, id});
    E[id++] = c;
    G[b].push_back({a, id++});
}

//Tworzenie grafu BFS:
bool bfs(int src)
{
    //Zerowanie odległości i czyszczenie grafu BFS
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

            //Jeżeli nieodwiedzony oraz dodatnia przepustowość:
            if (!dist[u] && E[x])
            {
                dist[u] = dist[v] + 1;
                Q.push(u);
            }

            //Jeżeli krawędź (v, u) jest pomiędzy kolejnymi warstwami BFS:
            if (dist[u] == dist[v] + 1)
            {
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
        //Dotarłeś do ujścia
        return flow;
    }

    for (int i = 0; i < GL[v].size(); i++)
    {
        auto e = GL[v][i];
        int u = e.st, x = e.nd;

        int f = E[x];
        if (f) f = dfs(u, min(flow, f));
        if (!f) //Krawędź (v, u) NIE należy do żadnej ścieżki powiększającej
        {
            //Usunięcie zbędnej krawędzi:
            swap(GL[v][i], GL[v].back());
            GL[v].pop_back();
            i--;
            continue;
        }

        //Krawędź (v, u) należy do ścieżki powiększającej
        E[x] -= f;
        E[x ^ 1] += f; //ID krawędzi przeciwnej do x to (x ^ 1)
        return f;
    }

    return 0; //Nie znaleziono ścieżki powiększającej
}

ll dinic(int src)
{
    ll flow = 0;
    while (bfs(src)) //Dopóki istnieje ścieżka powiększająca w grafie G
    {
        while (int f = dfs(src, inf)) //Dopóki istnieje ścieżka powiększająca w grafie BFS
        {
            flow += f;
        }
    }
    return flow;
}
