//Oblicza głębokości wierzchołków i rozmiary poddrzew
//Złożoność O(|V| + |E|)

const int MAXN = 1e6+5;
int sz[MAXN], d[MAXN]; //Rozmiary poddrzew, głębokości wierzchołków
vector<int> G[MAXN]; //Graf

void dfs(int v, int p)
{
    sz[v] = 1;
    for (int u : G[v])
    {
        if (u == p) continue;
        d[u] = d[v] + 1;
        dfs(u, v);
        sz[v] += sz[u];
    }
}
