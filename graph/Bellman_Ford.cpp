//Oblicza długości najkrótszych ścieżek od wierzchołka startowego do każdego innego
//Jeżeli występuje ujemny cykl to zwraca 0
//Złożoność O(|V| * |E|)

const int MAXN = 1e4+5, INF = 1e9;
int dist[MAXN]; //Odległości
vector<pair<pair<int, int>, int>> E; //Krawędź (v, u) o wadze w

bool relax()
{
    bool ok = 1;
    for (auto e : E)
    {
        int v = e.st.st, u = e.st.nd, w = e.nd;
        if (dist[u] > dist[v] + w)
        {
            ok = 0;
            dist[u] = dist[v] + w;
        }
    }
    return ok;
}
bool bellman_ford(int start, int n)
{
    for (int i = 1; i < MAXN; i++) dist[i] = INF;
    dist[start] = 0;
    //Próbuje skrócić odległości n-1 razy
    for (int i = 1; i < n; i++)
    {
        relax();
    }
    //Jeżeli da się za n-tym przejściem skrócić odległość to istnieje ujemny cykl
    return relax();
}
