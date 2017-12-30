//Algorytm Hopcrofta - Karpa znajdywania maksymalnego skojarzenia w grafie dwudzielnym
//Różni się od Kuhna tym, że szuka ścieżek powiększających tylko wśród najkrótszych
//ścieżek. Przed puszczeniem dfs puszcza bfs najpierw wrzucając na kolejkę nieskojarzone
//wierzchołki. Jeżeli rozważamy krawędź (v, u) i wierzchołek v ma odległość dist[v] to
//wierzchołek z którym jest skojarzony wierzchołek u będzie miał odległość dist[v] + 1.
//Złożoność O(|E| * sqrt(|V|))

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

    //Szuka scieżki powiększającej
    bool dfs(int v)
    {
        for (int u : G[v])
        {
            //Jeżeli nieskojarzony lub udało się znaleźć ścieżkę powiększającą
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
        //Jeżeli znalazł ścieżkę powiększającą to dist[0] > 1
        return dist[0];
    }

    //Zwraca wektor z krawędziami należącymi do maksymalnego skojarzenia
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
