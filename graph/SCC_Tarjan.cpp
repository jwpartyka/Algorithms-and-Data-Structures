//Dzieli graf na silnie spójne przy użyciu algorytmu Tarjana
//Algorytm wymaga tylko jednego przejścia dfs
//Jeżeli sąsiad u wierzchołka v jest odwiedzony (lov[u] > 0), ale nie znajduje się
//stosie to znaczy, że u znajduje się już w jakiejś silnie spójnej oraz SCC[u] != SCC[v]
//Wchodząc do wierzchołka v wrzuca go na stos, a wychodząc sprawdza czy jest "korzeniem"
//jakiejś silnie spójnej (low[v] == pre[v]). Jeżeli tak to wyrzuca wszystkie wierzchołki
//z wierzchu stosu dopóki nie trafi na v. Zrzucając ze stosu dodaje krawędzie do grafu SCC.

const int MAXN = 1e6 + 5;

int low[MAXN], pre[MAXN], SCC[MAXN], tim = 1, num = 1;
bool used[MAXN];
vector<int> G[MAXN], Gscc[MAXN];
stack<int> St;

void dfs(int v)
{
    low[v] = pre[v] = tim++;
    St.push(v);
    used[v] = 1;
    for (int u : G[v])
    {
        if (low[u])
        {
            if (used[u]) low[v] = min(low[v], pre[u]);
        }
        else
        {
            dfs(u);
            low[v] = min(low[v], low[u]);
        }
    }

    if (low[v] != pre[v]) return ;
    
    int cur = v;
    do
    {
        v = St.top();
        St.pop();
        used[v] = 0;
        SCC[v] = num;
        for (int u : G[v])
        {
            if (SCC[u] && SCC[v] != SCC[u])
            {
                Gscc[SCC[v]].push_back(SCC[u]);
            }
        }
    } while (v != cur);
    num++;
}

void sccBuild(int n)
{
    for (int i = 1; i <= n; i++)
    {
        if (!low[i]) dfs(i);
    }
}
