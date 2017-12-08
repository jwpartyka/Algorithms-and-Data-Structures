//Oblicza długości najkrótszych ścieżek od wierzchołka startowego do każdego innego
//Nie działa gdy jest ujemny cykl w grafie
//Złożoność O(|E| * log|V|)

#define st first
#define nd second

const int MAXN = 5e5+5, INF = 1e9;
int dist[MAXN]; //Odległości
vector<pair<int, int>> G[MAXN]; //Graf
priority_queue<pair<int, int> > Q; //Kolejka do dijkstry, trzyma {-dist[v], v}

void dijkstra(int start)
{
    for (int i = 1; i < MAXN; i++) dist[i] = INF;
    dist[start] = 0;
    Q.push({0, start});
    while (!Q.empty())
    {
        int v = Q.top().nd;
        int ww = Q.top().st;
        Q.pop();
        //Jeżeli dist[v] jest mniejsze niż w czasie wrzucenia v na kolejkę to nie rozważaj wierzchołka v
        if (ww > dist[v]) continue;
        for (auto i : G[v])
        {
            int u = i.st, w = i.nd;
            if (dist[u] > dist[v] + w)
            {
                dist[u] = dist[v] + w;
                //Wrzuć na kolejkę z ujemną odległością - priority_queue sortuje malejąco
                Q.push({-dist[u], u});
            }
        }
    }
}
