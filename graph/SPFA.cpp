//Oblicza długości najkrótszych ścieżek od wierzchołka startowego do każdego innego
//Jeżeli występuje ujemny cykl to zwraca 0
//Na grafach z dodatnimi wagami na krawędziach lepiej używać Dijkstry
//Z reguły działa szybciej od Bellmana-Forda, ale pesymistycznie tak samo
//Warto użyć przy znajdywaniu maksymalnego przepływu o minimalnym koszcie

#define st first
#define nd second

const int MAXN = 5e5+5, INF = 1e9;
int dist[MAXN]; //Odległości
vector<pair<int, int>> G[MAXN]; //Graf
queue<pair<int, int>> Q; //Kolejka do SPFA
int relax[MAXN]; //relax[v] - ile razy skrócono ścieżkę do v

bool SPFA(int start, int n)
{
    for (int i = 1; i <= n; i++) dist[i] = INF;
    dist[start] = 0;
    Q.push({0, start});
    while(!Q.empty())
    {
        int v = Q.front().nd;
        int ww = Q.front().st;
        Q.pop();
        if (dist[v] < ww) continue;
        for (auto e : G[v])
        {
            int u = e.st, w = e.nd;
            if (dist[u] > dist[v] + w)
            {
                relax[u]++;
                //Jeżeli nie ma ujemnego cyklu to relax[u] < n
                if (relax[u] == n) return 0;
                dist[u] = dist[v] + w;
                Q.push({dist[u], u});
            }
        }
    }
    return 1;
}
