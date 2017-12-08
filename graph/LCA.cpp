//Oblicza najniższego wspólnego przodka jump pointerami
//Złożoność preprocessingu: O((|V| + |E|) * log|V|)
//Złożoność LCA(a, b): O(log|V|)

const int MAXN = 5e5+5, LOG = 20;

int pre[MAXN], post[MAXN], lcap[MAXN][LOG+3], tim; //Numery pre- i postorder, przodkowie o 2^i w górę, czas odwiedzania wierzchołków
vector<int> G[MAXN]; //Graf

void preprocessing(int v, int p)
{
    lcap[v][0] = p, pre[v] = ++tim;
    for (int i = 1; i <= LOG; i++)
    {
        lcap[v][i] = lcap[lcap[v][i-1]][i-1];
    }
    for (int u : G[v])
    {
        if (u == p) continue;
        preprocessing(u, v);
    }
    post[v] = tim;
}

int LCA(int a, int b)
{
    if (pre[b] <= pre[a] && post[b] >= pre[a]) return b;
    for (int i = LOG; i >= 0; i--)
    {
        if (pre[lcap[b][i]] > pre[a] || post[lcap[b][i]] < pre[a])
        {
            b = lcap[b][i];
        }
    }
    return lcap[b][0];
}
