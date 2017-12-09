//Znajduje dekompozycje hld - wyznacza ciężkie ścieżki i lekkie krawędzie
//Można zmienić operacje drzewa przedziałowego w miarę potrzeb
//Złożoność preprocessingu O(|V| + |E|)
//Złożoność zapytania w wierzchołku O(log|V|)
//Złożoność zapytania na ścieżce O(log^2|V|)

const int MAXN = 2e5+5;
int sz[MAXN], heavy[MAXN], pre[MAXN], post[MAXN], id[MAXN], par[MAXN], beg[MAXN], Tree[2*1024*1024], Base = 1, tim, nr;
//sz - rozmiar poddrzewa, heavy - syn po krawedzi ciezkiej, pre - numer preoder, post - numer postorder,
//id - numer liscia w drzewie przedzialowym, par - ojciec w drzewie, beg - najwyzszy wierzcholek sciezki hld
vector<int> G[MAXN]; //Graf

//Liczenie tablic: sz, par, heavy, pre, post
void calcVertices(int v, int p)
{
    sz[v] = 1, par[v] = p, heavy[v] = v, pre[v] = ++tim;
    for (int u : G[v])
    {
        if (u == p) continue;
        calcVertices(u, v);
        if (sz[u] >= sz[heavy[v]]) heavy[v] = u; // Znalazlem syna z wiekszym poddrzewem
        sz[v] += sz[u];
    }
    post[v] = tim;
}

//Liczenie tablic: beg, id
void calcPaths(int v, int p, int d)
{
    for (int u : G[v])
    {
        if (u == p) continue;
        if (heavy[v] == u)
        {
            beg[u] = beg[v];
            calcPaths(u, v, d+1);
        }
        else
        {
            beg[u] = u;
            calcPaths(u, v, 0);
        }
    }
    if (heavy[v] == v) id[v] = nr++;
    else
    {
        id[v] = id[heavy[v]] + 1;
        nr = max(nr, id[v] + d + 1);
    }
}


//Do zmiany w miarę potrzeb:
void chTree(int node, int left, int right, int l, int r, int v)
{
    if (l <= left && right <= r)
    {
        Tree[node] = v;
        return;
    }
    int mid = (left + right) / 2;
    if (l <= mid) chTree(2*node, left, mid, l, r, v);
    if (mid + 1 <= r) chTree(2*node+1, mid+1, right, l, r, v);
    Tree[node] = Tree[2*node] + Tree[2*node+1];
}
//Do zmiany w miarę potrzeb:
int read(int node, int left, int right, int l, int r)
{
    if (l <= left && right <= r)
    {
        return Tree[node];
    }

    int mid  = (left + right) / 2, res = 0;
    if (l <= mid) res += read(2*node, left, mid, l, r);
    if (mid+1 <= r) res += read(2*node+1, mid+1, right, l, r);
    return res;
}

int res;
//Przesuwam a w górę drzewa po sciezkach dopóki b nie jest w poddrzewie beg[a]
int toLCA(int a, int b, bool op)
{
    while (pre[beg[a]] > pre[b] || post[beg[a]] < pre[b])
    {
        if (op) // res = zczytaj z drzewa przedzialowego na sciezce id[a] --- id[beg[a]]
        else // zaktualizuj sciezke id[a] --- id[beg[a]]
        a = par[beg[a]];
    }
    return a;
}

//Zapytanie na sciezce a --- b -> a != b lub a == b
//Zapytanie w wierzcholku -> a == b
//op == 1 -> odczyt, op == 0 -> zmiana
void processQuery(int a, int b, bool op)
{
    res = 0;
    a = toLCA(a, b, op);
    b = toLCA(b, a, op);
    if (id[a] > id[b]) swap(a, b); // lca(a, b) = b;
    if (op) // res = czytaj z drzewa przedzialowego na sciezce id[a] --- id[b]
    else //zaktualizuj sciezke id[a] --- id[b]
}

void przygotuj()
{
    preprocessing(1, 1);
    beg[1] = 1;
    hldBuild(1, 1, 0);
}
