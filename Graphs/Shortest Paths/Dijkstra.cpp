// Computes shortest paths from the source to every other vertex
// Doesn't work with negative weights
// Complexity: O(|E| * log|V|)
// Usage: [SPOJ] EZDIJKST http://www.spoj.com/problems/EZDIJKST/

#define st first
#define nd second

const int MAXN = 5e5+5, INF = 1e9;
int dist[MAXN]; // Distances from the source
vector<pair<int, int>> G[MAXN]; // Graph
priority_queue<pair<int, int> > Q; // Priority queue for Dijkstra

void dijkstra(int start)
{
    for (int i = 1; i < MAXN; i++) dist[i] = INF;
    dist[start] = 0;
    Q.push({0, start});
    while (!Q.empty())
    {
        int v = Q.top().nd;
        int w = Q.top().st;
        Q.pop();
        // If dist[v] is smaller than it was at the time of adding v to the queue then don't process v
        if (w > dist[v]) continue;
        for (auto i : G[v])
        {
            int u = i.st, w = i.nd;
            if (dist[u] > dist[v] + w)
            {
                dist[u] = dist[v] + w;
                // Add to the queue with negative distance - priority_queue sorts decreasingly
                Q.push({-dist[u], u});
            }
        }
    }
}
