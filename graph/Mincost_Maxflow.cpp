//Znajdywanie maksymalnego przepływu o minimalnym koszcie
//Przepływ o maksymalnym koszcie to mincost na grafie z przeciwnymi wagami
//Złożoność: O((|V| * |E|) + (|E| * log |V|) * (|V| * |E|)) =
//         = O(|E| ^ 2 * |V| * log |V|)

#define st first
#define nd second

using ll = long long;

const int MAXN = 555, inf = 1e9;
const ll INF = 1e18;

struct edge
{
    int f, w;
};

struct Edge
{
    int v, u, w;
};

struct Dijkstra
{
    int v, f;
    ll w;
    bool operator < (const Dijkstra &b) const
    {
        return w < b.w;
    }
};

int n, t, id; //Liczba wierzchołków, numer ujścia, id krawędzi
ll dist[MAXN], h[MAXN]; //Odległości od źródła, potencjały
pair<int, int> p[MAXN]; //Poprzednicy w dijkstrze
vector<pair<int, int>> G[MAXN]; //Graf
edge E[MAXN * MAXN]; //Własności krawędzi grafu
vector<Edge> edges; //Lista krawędzi do Bellmana - Forda

//Krawędź (a, b) o przepustowości c i wadze w oraz krawędź do niej przeciwna:
inline void addEdge(int a, int b, int c, int w)
{
    edges.push_back({a, b, w});
    G[a].push_back({b, id});
    E[id++] = {c, w};
    G[b].push_back({a, id});
    E[id++] = {0, -w};
}

//Liczenie potencjałów:
bool bellman_ford(int src)
{
    for (int i = 0; i <= n; i++)
    {
        h[i] = INF;
    }

    h[src] = 0;

    for (int i = 1; i <= n; i++)
    {
        for (auto e : edges)
        {
            int v = e.v, u = e.u, w = e.w;
            if (h[u] > h[v] + w)
            {
                if (i == n) return 0;
                h[u] = h[v] + w;
            }
        }
    }
    return 1;
}

int dijkstra(int src)
{
    for (int i = 0; i <= n; i++)
    {
        dist[i] = INF;
    }

    priority_queue<Dijkstra> Q;
    Q.push({src, inf, 0});
    dist[src] = 0;

    while (!Q.empty())
    {
        int v = Q.top().v, flow = Q.top().f;
        ll w = Q.top().w;
        Q.pop();
        if (w > dist[v]) continue;

        if (v == t)
        {
            //Jesteś w ujśiu - znaleziono ścieżkę powiększającą
            return flow;
        }

        for (auto e : G[v])
        {
            int u = e.st, x = e.nd;
            ll w = E[x].w + h[v] - h[u];
            int f = E[x].f;
            if (dist[u] > dist[v] + w && f)
            {
                dist[u] = dist[v] + w;
                p[u] = {v, x};
                Q.push({u, min(flow, f), dist[u]});
            }
        }
    }
    return 0; //Brak ścieżki powiększającej
}

pair<ll, ll> mincostflow(int src)
{
    //Czy istnieje ujemny cykl:
    if (!bellman_ford(src)) return {0, INF};

    ll flow = 0, cost = 0;
    while (int f = dijkstra(src)) //Dopóki istnieje ścieżka powiększająca
    {
        flow += f;
        int v = t;
        while (v != src)
        {
            int x = p[v].nd;
            cost += E[x].w * f;
            E[x].f -= f;
            E[x ^ 1].f += f;
            v = p[v].st;
        }
    }
    return {flow, cost};
}
