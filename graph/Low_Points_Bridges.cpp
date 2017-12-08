//1) Liczy wartość funkcji low dla każdego wierzchołka
//2) Znajduje mosty
//3) Znajduje punkty artykulacji
//Złożoność O(|V| + |E|)

#define st first
#define nd second

const int MAXN = 1e6+5;
int pre[MAXN], low[MAXN], tim; //numery preorder, wartości funkcji low, czas odwiedzenia wierzchołka
bool vis[MAXN]; //tablica odwiedzonych
vector<int> G[MAXN], points; //graf, punkty artykulacji
vector<pair<int, int>> bridges; //mosty

void calcLow(int v, int p)
{
    vis[v] = 1, pre[v] = tim++, low[v] = pre[v];
    bool ok = 0;
    for (int u : G[v])
    {
        if (u == p) continue;
        //1)
        if (vis[u]) low[v] = min(low[v], pre[u]);
        else
        {
            calcLow(u, v);
            low[v] = min(low[v], low[u]);
        }
        //2) Sprawdzenie czy krawędź (v, u) jest mostem
        if (low[u] > pre[v]) bridges.push_back({v, u});

        //3) Jeżeli jeszcze nie stwierdziłem że v jest punktem artykulacji to sprawdź go
        if (ok) continue;
        if (low[u] >= pre[v])
        {
            //Jeżeli korzeń ma tylko jednego syna to nie jest punktem artykulacji
            if (v == 0 && G[v].size() == 1) continue;
            points.push_back(v);
            ok = 1;
        }
    }
}
