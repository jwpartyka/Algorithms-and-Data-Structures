//Algorytm Kuhna (Turbo Matching) znajdywania maksymalnego skojarzenia w grafie dwudzielnym
//Złożoność O(|V| * |E|)

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

    //Szuka scieżki powiększającej
    bool dfs(int v)
    {
        if (vis[v] == nr) return 0;
        vis[v] = nr;
        for (int u : G[v])
        {
            //Jeżeli nieskojarzony lub udało się znaleźć ścieżkę powiększającą
            if (!match[u] || dfs(match[u]))
            {
                match[v] = u;
                match[u] = v;
                return 1;
            }
        }
        return 0;
    }

    //Zwraca wektor z krawędziami należącymi do maksymalnego skojarzenia
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
