// Hopcroft - Karp algorithm for finding maximum bipartite matching.
// It looks for augmenting paths only among the shortes paths.
// Before running a DFS it adds "unmatched" vertices to the queue and runs a BFS.
// If we consider an edge (v, u) and distance to vertex v is dist[v] then
// distance to vertex which is matched with u is dist[v] + 1
// Complexity: O(|E| * |V|^(1/2))
// Usage: [SPOJ] MATCHING http://www.spoj.com/problems/MATCHING/

struct HK
{
    vector<int> match, dist;
    vector<vector<int>> G;
    int n, m;

    HK(int n, int m) : n(n), m(m), dist(n + 3, 0),  match(n + m + 3, 0), G(n + 3) {}

    inline void addEdge(int a, int b)
    {
        G[a].push_back(b);
    }

    // Looks for an augmentive path
    bool dfs(int v)
    {
        for (int u : G[v])
        {
            // If u isn't matched or an augmentive path was found
            if (!match[u] || (dist[match[u]] == dist[v] + 1 && dfs(match[u])))
            {
                match[v] = u;
                match[u] = v;
                return 1;
            }
        }
        dist[v] = 0;
        return 0;
    }

    bool bfs()
    {
        static queue<int> Q;
        for (int i = 1; i <= n; i++)
        {
            if (!match[i])
            {
                dist[i] = 1;
                Q.push(i);
            }
            else dist[i] = 0;
        }
        dist[0] = 0;
        while (!Q.empty())
        {
            int v = Q.front();
            Q.pop();
            for (int u : G[v])
            {
                if (!dist[match[u]])
                {
                    dist[match[u]] = dist[v] + 1;
                    Q.push(match[u]);
                }
            }
        }

        // If an augmentive path was found dist[0] would be positive
        return dist[0];
    }

    // Returns edges belonging to the maximum matching
    vector<pair<int, int>> maxMatching()
    {
        vector<pair<int, int>> matching;
        while (bfs())
        {
            for (int i = 1; i <= n; i++)
            {
                if (!match[i] && dfs(i))
                {
                    matching.push_back({i, match[i]});
                }
            }
        }
        return matching;
    }
};
