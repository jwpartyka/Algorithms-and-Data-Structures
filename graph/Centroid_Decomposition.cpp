//Znajduje dekompozycje drzewa na centroidy
//Wyznacza stopnie centroidów i centroidowych rodziców
//Złożoność O((|V| + |E|) * log|V|)

const int MAXN = 5e5+5;
int sz[MAXN], cd[MAXN], cdp[MAXN]; //Rozmiary poddrzew, stopnie centroidów, centroidowi rodzice
vector<int> G[MAXN]; //Graf

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
void cdCalc(int v, int p)
{
    cdp[v] = p;
    cd[v] = cd[cdp[v]] + 1;
    /*...*/
}
void cdBuild(int v, int p)
{
    calcSizes(v, -1); //Oblicza rozmiary poddrzew
    v = cdFind(v, -1); //Znajduje centroid
    cdCalc(v, p); //Przerabia centroid
    for (int u : G[v])
    {
        if (cd[u]) continue;
        cdBuild(u, v);
    }
}
void ansQuery(int v)
{
    /* ... */
}
void update(int v)
{
    /* ... */
}
