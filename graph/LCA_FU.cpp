//Znajdywanie LCA offline przy użyciu FU
//Złożoność: O(N * log*N)

#include <iostream>
#include <vector>
#define st first
#define nd second

using namespace std;

const int MAXN = 5e5+5;

struct fu
{
    int head, rank;
};
fu FU[MAXN];

void initSet(int a)
{
    FU[a].head = a;
}

int FIND(int a)
{
    if (a != FU[a].head) FU[a].head = FIND(FU[a].head);
    return FU[a].head;
}

void UNION(int a, int b)
{
    a = FIND(a), b = FIND(b);
    FU[b].head = a;
}

struct query
{
    int a, b, lca;
};
vector<query> queries; //Wektor przechowujący zapytania
vector<int> zap[MAXN], G[MAXN]; //zap[v] - zapytania dotyczące wierzchołka v, G - graf

void calcLCA(int v, int p)
{
    //Znajdywanie odpowiedzi dla zapytań dotyczących wierzchołka v
    for (int q : zap[v])
    {
        int a = queries[q].a, b = queries[q].b;
        if (v == a) queries[q].lca = FIND(b);
        else queries[q].lca = FIND(a);
    }
    for (int u : G[v])
    {
        if (u == p) continue;
        calcLCA(u, v);
        UNION(v, u);
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        initSet(i);
    }
    for (int i = 1; i < n; i++)
    {
        int a, b;
        cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }

    int a, b, id = 0;
    cin >> a;
    while (a != -1)
    {
        cin >> b;
        queries.push_back({a, b, 0});
        zap[a].push_back(id), zap[b].push_back(id++);
        cin >> a;
    }
    calcLCA(1, -1);
    for (auto q : queries)
    {
        cout << q.lca << "\n";
    }
}
