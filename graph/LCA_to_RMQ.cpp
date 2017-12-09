//Zamiana problemu LCA na RMQ, znajdywanie LCA w czasie stałym
//Złożoność preprocessingu O(N * logN)
//Złożoność zapytania: O(1)

#include <iostream>
#include <vector>
#define st first
#define nd second

using namespace std;
using ll = long long;

const int MAXN = 1e6+5, LOG = 22;
int pre[MAXN], RMQ[MAXN][LOG+3], tim, real[MAXN], pos[MAXN];
//pre - numery preorder, tim - czas odwiedzenia wierzchołka,
//real - zamiana pre[v] na v, pos - indeks w wektorze tab
vector<int> G[MAXN], tab; //Graf, wektor do RMQ

void LCA_to_RMQ(int v, int p)
{
    pre[v] = ++tim;
    real[pre[v]] = v;
    for (int u : G[v])
    {
        if (u == p) continue;
        LCA_to_RMQ(u, v);
        tab.push_back(pre[v]);
    }
    tab.push_back(pre[v]);
    pos[v] = tab.size()-1;
}

void preprocessing(int n)
{
    for (int i = 0; i < n; i++)
    {
        RMQ[i][0] = tab[i];
    }
    for (int p = 1; (1<<p) <= n; p++)
    {
        for (int i = 0; i < n; i++)
        {
            if (i+(1<<p) > n) RMQ[i][p] = RMQ[i-1][p];
            else RMQ[i][p] = min(RMQ[i][p-1], RMQ[i+(1<<(p-1))][p-1]);
        }
    }
}

int minimum(int l, int r)
{
    if (l > r) swap(l, r);
    if (l == r) return tab[l];
    int x = (r-l+1);
    int p = 31 - __builtin_clz(x);
    return min(RMQ[l][p], RMQ[r-(1<<p)+1][p]);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    for (int i = 1; i < n; i++)
    {
        int a, b;
        cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }
    LCA_to_RMQ(1, -1);
    preprocessing(tab.size());
    int q;
    cin >> q;
    while(q--)
    {
        int a, b;
        cin >> a >> b;
        int lca = real(minimum(pos[a], pos[b]));
        cout << lca << "\n";
    }
}
