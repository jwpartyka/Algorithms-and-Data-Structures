// Centroid Decomposition
// Computes depths of centroids and their centroid parents
// Complexity: O((|V| + |E|) * log |V|)
// Usage: [CF Round #190] Ciel the Commander http://codeforces.com/problemset/problem/321/C
//        [IOI 2011] Race https://wcipeg.com/problem/ioi1112

const int MAXN = 5e5+5;

int sz[MAXN], cd[MAXN], cdp[MAXN]; // Sizes of subtrees, centroid depths, centroid parents
vector<int> G[MAXN]; // Graph

// Computes sizes of subtrees
void calcSizes(int v, int p)
{
    sz[v] = 1;
    for (int u : G[v])
    {
        if (cd[u]) continue;
        calcSizes(u, v);
        sz[v] += sz[u];
    }
}

// Finds a centroid
int cdFind(int v, int p)
{
    int tot = sz[v];
    bool ok = 0;
    while (!ok)
    {
        ok = 1;
        for (int u : G[v])
        {
            if (cd[u] || u == p || sz[u] * 2 <= tot) continue;
            p = v, v = u, ok = 0;
            break;
        }
    }
    return v;
}

// Processes centroid
void cdCalc(int v, int p)
{
    cdp[v] = p;
    cd[v] = cd[cdp[v]] + 1;
    /*...*/
}

// Decomposes the tree
void cdBuild(int v, int p)
{
    calcSizes(v, -1); // Computes sizes of subtrees
    v = cdFind(v, -1); // Finds a centroid
    cdCalc(v, p); // Processes centroid
    for (int u : G[v])
    {
        if (cd[u]) continue;
        cdBuild(u, v);
    }
}

void query(int v)
{
    /* ... */
}

void update(int v)
{
    /* ... */
}
