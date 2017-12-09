//Znajdywanie MST przy użyciu priority_queue (algorytm Prima)
//Złożoność O(|E| * log|E|)
//Działa szybciej od MST z FU w przypadku kliki

#define st first
#define nd second

const int MAXN = 5e5+5;
bool vis[MAXN], used[MAXN]; //Tablica określająca czy dany wierzchołek należy do MST
vector<pair<int, int>> G[MAXN], MST[MAXN]; //Początkowy graf, MST
priority_queue<pair<int, int>> Q; //Kolejka do znajdywania MST

void findMST()
{
    Q.push({0, 1});
    while(!Q.empty())
    {
        int v = Q.top().nd;
        Q.pop();
        if (vis[v]) continue;
        vis[v] = 1;
        for (auto e : G[v])
        {
            int u = e.st, w = e.nd;
            if(used[u]) continue;
            used[u] = 1;
            MST[v].push_back({u, w});
            MST[u].push_back({v, w});
            Q.push({-w, u});
        }
    }
}
