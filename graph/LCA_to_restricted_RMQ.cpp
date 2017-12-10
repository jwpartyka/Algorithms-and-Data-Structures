//Znajdywanie LCA w czasie stałym po liniowym preprocessingu
//Złożoność czasowa preprocessingu: O(|V|) <-- Stała rzędu kilkanaście
//Złożoność czasowa zapytania: O(1)
//Złożoność pamięciowa programu: O(|V|) <-- Stała rzędu kilkanaście, dla N <= 500 000 ---> ~30MB
//Algorytm sprowadza LCA do problemu RMQ w czasie liniowym
//Dodatkowo każda kolejna wartość w tablicy różni się o 1
//dlatego preprocessing można zrobić w czasie liniowym, a nie liniowo - logarytmicznym jak w zwykłym RMQ

const int MAXN = 1e6+5, LOG = 20, logg = 10, maxn = 2*MAXN/LOG+5, INF = 2e6;
//MAXN = 2 * limit na N, LOG = log(N), logg = 0.5 * log(N), maxn = 4*N/log(N) = 2*MAXN/LOG

int ET[MAXN], D[MAXN], pierwsze[MAXN], group[maxn][logg+1], hasz[maxn], groupID[maxn], lookup[2000][logg+1][logg+1], ST[maxn][LOG], N, nr;
//ET - Euler Tour grafu G, D - głebokości wierzchołków z ET, pierwsze[i] - indeks pierwszego wystąpiena i w ET,
//group - podzial D na grupy o rozmiarze 0.5 * logN, hasz - hasze różnych rodzajów grup, groupID - hasze grup po przenumerowaniu,
//lookup - wyniki dla różnych grup, ST - Sparse Table dla minimów ze wszystkich grup
vector<int> G[MAXN]; //Graf
map<int, int> M; //Mapa do przenumerowania haszy grup
int p = 997; //Podstawa do haszowania

void dodaj(int v, int d)
{
    D[N] = d;
    ET[N] = v;
    N++;
}
//Liczenie ET i D
void preprocessing(int v, int p, int d)
{
    pierwsze[v] = N;
    dodaj(v, d);
    for (int u : G[v])
    {
        if (u == p) continue;
        preprocessing(u, v, d+1);
        dodaj(v, d);
    }
}

//Obliczanie wyników dla l-tej grupy
void calcLookup(int k, int l)
{
    for (int i = 0; i < logg; i++)
    {
        lookup[l][i][i] = i;
        for (int j = i+1; j < logg; j++)
        {
            if (k*logg+j >= N) break;
            if (group[k][j] < D[k*logg + lookup[l][i][j-1]]) lookup[l][i][j] = j;
            else lookup[l][i][j] = lookup[l][i][j-1];
        }
    }
}

//Podział D na grupy
void divide_into_groups()
{
    for (int i = 0; i <= N/logg; i++)
    {
        for (int j = 0; j < logg; j++) group[i][j] = INF;
        ST[i][0] = N;
    }

    //Wyznaczanie i haszowanie grup
    for (int i = 0; i < N; i++)
    {
        int x = i/logg, y = i%logg;
        group[x][y] = D[i];
        hasz[x] = hasz[x] * p + group[x][y] - group[x][0] + 1;
        if (D[i] < D[ST[x][0]]) ST[x][0] = i;
    }

    //Przenumerowanie haszy
    for (int i = 0; i <= N/logg; i++)
    {
        if (M[hasz[i]] == 0)
        {
            M[hasz[i]] = ++nr;
            calcLookup(i, nr-1);
        }
        groupID[i] = M[hasz[i]] - 1;
    }

    //Obliczanie ST
    for (int j = 1; (1<<j) <= N/logg+1; j++)
    {
        for (int i = 0; i + (1<<j) -1 < N/logg+1; i++)
        {
            ST[i][j] = ST[i][j-1];
            if (D[ST[i + (1<<(j-1))][j-1]] < D[ST[i][j]]) ST[i][j] = ST[i + (1<<(j-1))][j-1];
        }
    }
}

int LCA(int l, int r)
{
    l = pierwsze[l], r = pierwsze[r];
    if (l > r) swap(l, r);
    int x = l/logg, y = r/logg;
    if (x == y)
    {
        int mini = x*logg + lookup[groupID[x]][l%logg][r%logg];
        return ET[mini];
    }
    
    //Znalezienie minimum w lewej grupie
    int mini = x * logg + lookup[groupID[x]][l%logg][logg-1];
    int val = D[x * logg + lookup[groupID[x]][l%logg][logg-1]];
    
    //Znalezienie minimum w prawej grupie
    if (val > D[y * logg +lookup[groupID[y]][0][r%logg]])
    {
        mini = y * logg + lookup[groupID[y]][0][r%logg];
        val = D[y * logg + lookup[groupID[y]][0][r%logg]];
    }
    
    x++, y--;
    if (x > y) return ET[mini];
    //Znalezienie minimum pomiędzy prawą a lewą grupą
    int len = 31 - __builtin_clz(y-x+1);
    if (val > D[ST[x][len]])
    {
        mini = ST[x][len];
        val = D[ST[x][len]];
    }
    if (val > D[ST[y - (1<<len) + 1][len]])
    {
        mini = ST[y - (1<<len) + 1][len];
    }
    return ET[mini];
}

void przygotuj()
{
    preprocessing(1, 1, 0);
    D[N] = INF;
    divide_into_groups();
}

//NIE POLECAM... :(
