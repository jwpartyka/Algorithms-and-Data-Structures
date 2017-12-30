//Sprawdza przy użyciu Bellmana - Forda czy istnieje ujemny cykl osiągalny z wierzchołka src
//Jeżeli chcemy znaleźć dowolny ujemny cykl to można do funkcji negCycle przekazać src = 0
//Jeżeli istnieje ujemny cykl to otrzymamy wektor z indeksami kolejnych krawędzi cyklu
//W przeciwnym wypadku uzupełnia tablicę dist najkrótszymi odległościami od src do każdego wierzchołka
//Złożoność: O(|V| * |E|)

#define st first
#define nd second

using ll = long long;

const int MAXN = 5e3+5;
const ll INF = 1e18;

struct edge
{
    int v, u, w, id;
};

ll dist[MAXN];
bool vis[MAXN];
pair<int, int> p[MAXN]; //Tablica poprzedników (wierzchołek, indeks krawędzi)
vector<edge> E; //Lista krawędzi (v, u, w, id)

vector<pair<int, int>> negCycle(int src, int n)
{
    for (int i = 1; i <= n; i++)
    {
        dist[i] = INF;
    }
    dist[src] = 0;

    vector<pair<int, int>> cycle;
    for (int i = 1; i <= n; i++)
    {
        for (auto e : E)
        {
            int v = e.v, u = e.u, w = e.w;
            if (dist[u] > dist[v] + w)
            {
                dist[u] = dist[v] + w;
                p[u] = {v, e.id};

                if (i == n)
                {
                    while (!vis[v])
                    {
                        vis[v] = 1;
                        cycle.push_back(p[v]);
                        v = p[v].st;
                    }
                    reverse(cycle.begin(), cycle.end());
                    while (cycle.back() != p[v])
                    {
                        cycle.pop_back();
                    }
                    break;
                }
            }
        }
    }

    return cycle;
}
