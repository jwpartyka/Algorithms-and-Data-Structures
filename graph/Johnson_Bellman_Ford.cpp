//Oblicza długości najkrótszych ścieżek pomiędzy każdą parą wierzchołków
//Używa Bellmana-Forda i Dijkstry
//Jeżeli występuje ujemny cykl to zwraca 0
//Złożoność O(|V|*|E|*log|V| + |V|*|E|)
//Jeżeli kolejkę priorytetową zrobi się kopcem Fibonacciego to złożoność będzie:
//O(|V|^2*log|V| + |V|*|E|)

#define st first
#define nd second

const int MAXN = 2e3+5, inf = 1e9;

struct edge
{
    int v, u, w;
};

int dist[MAXN][MAXN], h[MAXN]; //Odległości, potencjały
vector<pair<int, int>> G[MAXN]; //Graf
vector<edge> E; //Lista krawędzi do Bellmana-Forda
priority_queue<pair<int, int>> Q; //Kolejka do Dijkstry

bool bellman_ford(int n)
{
    for (int i = 1; i <= n; i++)
    {
        for (auto e : E)
        {
            int v = e.v, u = e.u, w = e.w;
            if (h[u] > h[v] + w)
            {
                if (i == n) return 0; //Występuje ujemny cykl
                h[u] = h[v] + w;
            }
        }
    }
    return 1;
}

void dijkstra(int src, int n)
{
    for (int i = 1; i <= n; i++) dist[src][i] = inf;

    dist[src][src] = 0;
    Q.push({0, src});

    while (!Q.empty())
    {
        int v = Q.top().nd, w = Q.top().st;
        Q.pop();
        if (dist[src][v] > w) continue;

        for (auto e : G[v])
        {
            int u = e.st, w = e.nd + h[v] - h[u];
            if (dist[src][u] > dist[src][v] + w)
            {
                dist[src][u] = dist[src][v] + w;
                Q.push({-dist[src][u], u});
            }
        }
    }
}

bool johnson(int n)
{
    if (bellman_ford(n)) //Oblicza potencjały, szuka ujemnego cyklu
    {
        for (int i = 1; i <= n; i++)
        {
            //Oblicza odległości pomiędzy każdą parą wierzchołków (i, v)
            dijkstra(i, n);
        }
        return 1;
    }
    return 0;
}
