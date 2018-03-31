// Kuhn's algorithm for finding maximum barpitite matching
// Complexity: O(|V| * |E|)
// Usage: [SPOJ] MATCHING http://www.spoj.com/problems/MATCHING/

struct Kuhn
{
    vector<int> match, vis;
    vector<vector<int>> G;
    int n, m, nr;

    Kuhn(int n, int m) : n(n), m(m), nr(1), match(n + m + 3), vis(n + 3), G(n + 3) {}

    inline void addEdge(int a, int b)
    {
        G[a].push_back(b);
    }

    // Looks for an augmenting path
    bool dfs(int v)
    {
        if (vis[v] == nr) return 0;
        vis[v] = nr;
        for (int u : G[v])
        {
            // If u isn't matched or an augmentive path was found
            if (!match[u] || dfs(match[u]))
            {
                match[v] = u;
                match[u] = v;
                return 1;
            }
        }
        return 0;
    }

    // Returns edges belonging to the maximum matchings
    vector<pair<int, int>> maxMatching()
    {
        vector<pair<int, int>> matching;
        bool ok = 1;
        while (ok)
        {
            ok = 0;
            for (int i = 1; i <= n; i++)
            {
                if (!match[i] && dfs(i))
                {
                    ok = 1;
                    matching.push_back({i, match[i]});
                }
            }
            nr++;
        }
        return matching;
    }
};
