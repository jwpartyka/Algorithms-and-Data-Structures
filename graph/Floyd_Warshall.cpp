//Oblicza długości najkrótszych ścieżek pomiędzy każdą parą wierzchołków
//Złożoność O(|V|^3)

const int MAXN = 5e2+5, INF = 1e9;
int dist[MAXN][MAXN]; //Odległości

void floyd_warshall(int n)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = i+1; j <= n; j++)
        {
            //Jeżeli jest krawędź (i, j) o wadze w(i, j) to dist[i][j] = w(i, j)
            if (!dist[i][j]) dist[i][j] = INF;
            if (!dist[j][i]) dist[j][i] = INF;
        }
    }

    for (int k = 1; k <= n; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
}
