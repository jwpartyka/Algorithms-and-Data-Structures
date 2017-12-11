//Oblicza długości najkrótszych ścieżek pomiędzy każdą parą wierzchołków
//Używa Bellmana-Forda i Dijkstry
//Jeżeli występuje ujemny cykl to zwraca 0
//Złożoność O(|V|*|E|*log|V| + |V|*|E|)
//Jeżeli kolejkę priorytetową zrobi się kopcem Fibonacciego to złożoność będzie:
//O(|V|^2*log|V| + |V|*|E|)

#define st first
#define nd second

const int MAXN = 2e3+5, INF = 1e9;
int dist[MAXN][MAXN], h[MAXN]; //Odległości, potencjały
vector<pair<int, int>> G[MAXN]; //Graf
vector<pair<pair<int, int>, int>> E; //Lista krawędzi do Bellmana-Forda
priority_queue<pair<int, int>> Q; //Kolejka do Dijkstry

bool relax()
{
    bool ok = 1;
    for (auto e : E)
    {
        int v = e.st.st, u = e.st.nd, w = e.nd;
        if (h[u] > h[v] + w)
        {
            ok = 0;
            h[u] = h[v] + w;
        }
    }
    return ok;
}
bool bellman_ford(int n)
{
    for (int i = 1; i < n; i++)
    {
        relax();
    }
    return relax();
}

void dijkstra(int v0, int n)
{
    for (int i = 1; i <= n; i++) dist[v0][i] = INF;
    dist[v0][v0] = 0;
    Q.push({0, v0});
    while (!Q.empty())
    {
        int v = Q.top().nd, ww = Q.top().st;
        Q.pop();
        if (dist[v0][v] > ww) continue;
        for (auto e : G[v])
        {
            int u = e.st, w = e.nd + h[v] - h[u];
            if (dist[v0][u] > dist[v0][v] + w)
            {
                dist[v0][u] = dist[v0][v] + w;
                Q.push({-dist[v0][u], u});
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
