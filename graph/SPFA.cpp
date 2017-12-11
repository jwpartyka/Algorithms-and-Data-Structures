//Oblicza długości najkrótszych ścieżek od wierzchołka startowego do każdego innego
//Jeżeli występuje ujemny cykl to zwraca 0
//Na grafach z dodatnimi wagami na krawędziach lepiej używać Dijkstry
//Z reguły działa szybciej od Bellmana-Forda, ale pesymistycznie tak samo
//Warto użyć przy znajdywaniu maksymalnego przepływu o minimalnym koszcie

#define st first
#define nd second

const int MAXN = 5e4+5, INF = 1e9;
int dist[MAXN], relax[MAXN]; //Odległości, relax[v] - ile razy skrócono ścieżkę do v
bool used[MAXN]; //Tablica mówiąca czy dany wierzchołek jest na kolejce
vector<pair<int, int>> G[MAXN]; //Graf
queue<int> Q; //Kolejka do SPFA

bool SPFA(int start, int n)
{
    for (int i = 1; i <= n; i++) dist[i] = INF;
    dist[start] = 0;
    Q.push(start);
    while(!Q.empty())
    {
        int v = Q.front();
        Q.pop();
        used[v] = 0, relax[v]++;
        //Jeżeli skrócono najkrótszą ściężkę do v n-ty raz to istnieje ujemny cykl
        if (relax[v] == n) return 0;
        for (auto e : G[v])
        {
            int u = e.st, w = e.nd;
            if (dist[u] > dist[v] + w)
            {
                dist[u] = dist[v] + w;
                if (used[u]) continue;
                used[u] = 1;
                Q.push(u);
            }
        }
    }
    return 1;
}
