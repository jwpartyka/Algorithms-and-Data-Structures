//Oblicza najkrótsze ścieżki od wierzchołka startowego do każdego innego
//Krawędzie mają wagi 0 lub x
//Złożoność O(|V| + |E|)

#define st first
#define nd second

const int MAXN = 1e6+5, INF = 1e9;
int dist[MAXN]; //Odległości
vector<pair<int, int>> G[MAXN]; //Graf, G[v] przechowuje {u, w} co oznacza krawedz (v, u) o wadze w
deque<int> Q; //Kolejka do BFS

void bfs(int start)
{
    for (int i = 1; i <= n; i++) dist[i] = INF;
    dist[start] = 0;
    Q.push_front(start);
    while (!Q.empty())
    {
        int v = Q.front();
        Q.pop_front();
        for (auto e : G[v])
        {
            int u = e.st, w = e.nd;
            if (dist[u] > dist[v] + w)
            {
                dist[u] = dist[v] + w;
                if (w) Q.push_back(u);
                else Q.push_front(u);
            }
        }
    }
}
