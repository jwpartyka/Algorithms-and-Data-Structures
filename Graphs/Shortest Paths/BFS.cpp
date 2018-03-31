// Computes shortest paths from the source to every other vertex
// Edges have unit weights
// Complexity: O(|V| + |E|)

const int MAXN = 1e6+5;
int dist[MAXN]; // Distances from the source
vector<int> G[MAXN]; // Graph
deque<int> Q; // Queue for BFS

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
