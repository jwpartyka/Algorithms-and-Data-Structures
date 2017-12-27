//Sortowanie topologiczne BFS
//Graf musi być DAGiem
//Po rozważeniu krawędzi (v, u) zmniejsza indeg[u] o 1
//Dodaje wierzchołek u na kolejkę jeżeli indeg[u] = 0
//Zdejmując wierzchołek z kolejki wrzuca go na stos

const int MAXN = 1e6+5;

int indeg[MAXN];
bool vis[MAXN];
vector<int> G[MAXN];
stack<int> topo;

void sortuj(int n)
{
    queue<int> Q;
    for (int i = 1; i <= n; i++)
    {
        if (!indeg[i])
        {
            Q.push(i);
        }
    }

    while (!Q.empty())
    {
        int v = Q.front();
        topo.push(v);
        Q.pop();
        for (int u : G[v])
        {
            indeg[u]--;
            if (!indeg[u])
            {
                Q.push(u);
            }
        }
    }
}
