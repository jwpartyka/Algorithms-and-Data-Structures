// Computes shortest paths from the source to every other vertex
// Edges have weights 0 or x
// Complexity: O(|V| + |E|)
// Usage: [SPOJ] KATHTHI http://www.spoj.com/problems/KATHTHI/
//        [TC] DoNotTurn https://community.topcoder.com/stat?c=problem_statement&pm=10337
//        [BAPC 13] Jailbreak http://codeforces.com/gym/100625/attachments

#define st first
#define nd second

const int MAXN = 1e6+5, INF = 1e9;
int dist[MAXN]; // Distances from the source
vector<pair<int, int>> G[MAXN]; // Graph
deque<int> Q; // Queue for BFS

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
