//Oblicza najkrótsze ścieżki od wierzchołka startowego do każdego innego
//Krawędzie mają wagi 1
//Złożoność O(|V| + |E|)

const int MAXN = 1e6+5;
int dist[MAXN]; //Odległości
vector<int> G[MAXN]; //Graf
queue<int> Q; //Kolejka do BFS

void bfs(int start)
{
    Q.push(start);
    while (!Q.empty())
    {
        int v = Q.front();
        Q.pop();
        for (int u : G[v])
        {
            if (vis[u]) continue;
            vis[u] = 1;
            dist[u] = dist[v] + 1;
            Q.push(u);
        }
    }
}
