//Znajdywanie LCA po częściowym preprocessingu z HLD
//Złożoność czasowa preprocessingu: O(|V| + |E|)
//Złożoność pamięciowa programu: O(|V|)
//Złożoność zapytania: O(log|V|)

const int MAXN = 1e6+5;
int dist[MAXN], sz[MAXN], pre[MAXN], post[MAXN], heavy[MAXN], par[MAXN], beg[MAXN], head[MAXN], tim, nr;
vector<int> G[MAXN];

void preprocessing(int v, int p)
{
    pre[v] = ++tim, heavy[v] = v, par[v] = p, sz[v] = 1;
    for (int u : G[v])
    {
        if (u == p) continue;
        dist[u] = dist[v] + w;
        preprocessing(u, v);
        if (sz[u] > sz[heavy[v]]) heavy[v] = u;
        sz[v] += sz[u];
    }
    if (heavy[v] == v) beg[v] = nr++;
    else head[v] = beg[heavy[v]];
    head[beg[v]] = v, post[v] = tim;
}

void przygotuj(int n)
{
    preprocessing(1, 1);
    for (int i = 1; i <= n; i++) beg[i] = head[beg[i]];
}

int toLCA(int a, int b)
{
    while (pre[beg[a]] > pre[b] || post[beg[a]] < pre[b])
    {
        a = par[beg[a]];
    }
    return a;
}

int LCA(int a, int b)
{
    a = toLCA(a, b);
    b = toLCA(b, a);
    return (pre[a] < pre[b] ? a : b);
}
