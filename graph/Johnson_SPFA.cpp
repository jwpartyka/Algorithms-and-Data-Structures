//Oblicza długości najkrótszych ścieżek pomiędzy każdą parą wierzchołków
//Używa SPFA i Dijkstry
//Jeżeli występuje ujemny cykl to zwraca 0
//Złożoność O(|V|*|E|*log|V| + |V|*|E|)
//Jeżeli Dijkstre zrobi się kopcem Fibonacciego to złożoność będzie:
//O(|V|^2*log|V| + |V|*|E|)

#define st first
#define nd second

const int MAXN = 2e3+5, INF = 1e9;
int dist[MAXN][MAXN], h[MAXN], relax[MAXN]; //Odległości, potencjały
bool used[MAXN]; //Tablica mówiąca czy dany wierzchołek jest na kolejce (SPFA)
vector<pair<int, int>> G[MAXN]; //Graf
priority_queue<pair<int, int>> PQ; //Kolejka do Dijkstry
queue<int> Q; //Kolejka do SPFA

bool SPFA(int v0, int n)
{
    for (int i = 1; i <= n; i++) h[i] = INF;
    h[v0] = 0;
    Q.push(v0);
    while (!Q.empty())
    {
        int v = Q.front();
        Q.pop();
        used[v] = 0, relax[v]++;
        //Jeżeli skrócono najkrótszą ściężkę do v n-ty raz to istnieje ujemny cykl
        if (relax[v] == n) return 0;
        for (auto e : G[v])
        {
            int u = e.st, w = e.nd;
            if (h[u] > h[v] + w)
            {
                h[u] = h[v] + w;
                if (used[u]) continue;
                used[u] = 1;
                Q.push(u);
            }
        }
    }
    return 1;
}

void dijkstra(int v0, int n)
{
    for (int i = 1; i <= n; i++) dist[v0][i] = INF;
    dist[v0][v0] = 0;
    PQ.push({0, v0});
    while (!PQ.empty())
    {
        int v = PQ.top().nd, ww = PQ.top().st;
        PQ.pop();
        if (dist[v0][v] > ww) continue;
        for (auto e : G[v])
        {
            int u = e.st, w = e.nd + h[v] - h[u];
            if (dist[v0][u] > dist[v0][v] + w)
            {
                dist[v0][u] = dist[v0][v] + w;
                PQ.push({-dist[v0][u], u});
            }
        }
    }
}

bool johnson(int n)
{
    //Dodanie superwierzchołka, z którego puścimy SPFA
    for (int i = 1; i <= n; i++) G[0].push_back({i, 0});
    if (SPFA(0, n)) //Oblicza potencjały, szuka ujemnego cyklu
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
