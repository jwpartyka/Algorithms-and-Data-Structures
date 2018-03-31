// Computing LCA in constant time after linear preprocessing
// Time complexity:
// 1) Preprocessing: O(|V|)
// 2) Query: O(1)
// Memory complexity: O(|V|) (with large constant; for N <= 500 000 ---> ~30MB)
// Algorithm reduces LCA to RMQ in linear time in such way that adjacent values in array differ by exactly 1
// That's why preprocessing can be done in linear time (but with large constant)
// Usage: You don't use this algorithm...

const int MAXN = 1e6+5, LOG = 20, logg = 10, maxn = 2*MAXN/LOG + 5, inf = 2e6;
// MAXN = 2 * mamimal N, LOG = log(N), logg = 0.5 * log(N), maxn = 4*N/log(N) = 2*MAXN/LOG

int ET[MAXN], D[MAXN], firs[MAXN], group[maxn][logg+1], hash[maxn], groupID[maxn], lookup[2000][logg+1][logg+1], ST[maxn][LOG], N, nr;
// ET[] - Euler Tour of graph G, D[] - depths of vertices from ET, firs[i] - indeks of the first occurrence of i in ET[],
// group[] - division of D[] into groups of size maxn, hash[] - hashes of every type of group, groupID[] - compressed hash[]
// lookup[] - lookup table for every type of group, ST[] - Sparse Table for minimas from each group
vector<int> G[MAXN]; // Graph
map<int, int> M; // Map for compression
int p = 997; // Base for hashing

void add(int v, int d)
{
    D[N] = d;
    ET[N] = v;
    N++;
}

// Computing ET[] and D[]
void preprocessing(int v, int p, int d)
{
    firs[v] = N;
    add(v, d);
    for (int u : G[v])
    {
        if (u == p) continue;
        preprocessing(u, v, d+1);
        add(v, d);
    }
}

// Computing lookup tables for the lth group
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

// Divides D[] into groups
void divide_into_groups()
{
    for (int i = 0; i <= N/logg; i++)
    {
        for (int j = 0; j < logg; j++) group[i][j] = INF;
        ST[i][0] = N;
    }

    // Hashes groups
    for (int i = 0; i < N; i++)
    {
        int x = i/logg, y = i%logg;
        group[x][y] = D[i];
        hash[x] = hash[x] * p + group[x][y] - group[x][0] + 1;
        if (D[i] < D[ST[x][0]]) ST[x][0] = i;
    }

    // Hash compression
    for (int i = 0; i <= N/logg; i++)
    {
        if (M[hash[i]] == 0)
        {
            M[hash[i]] = ++nr;
            calcLookup(i, nr-1);
        }
        groupID[i] = M[hash[i]] - 1;
    }

    // Computing ST[]
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
    l = firs[l], r = firs[r];
    if (l > r) swap(l, r);
    int x = l/logg, y = r/logg;
    if (x == y)
    {
        int mini = x*logg + lookup[groupID[x]][l%logg][r%logg];
        return ET[mini];
    }

    // Computing minimum in the left group
    int mini = x * logg + lookup[groupID[x]][l%logg][logg-1];
    int val = D[x * logg + lookup[groupID[x]][l%logg][logg-1]];
    // Computing minimum in the right group
    if (val > D[y * logg +lookup[groupID[y]][0][r%logg]])
    {
        mini = y * logg + lookup[groupID[y]][0][r%logg];
        val = D[y * logg + lookup[groupID[y]][0][r%logg]];
    }
    x++, y--;
    if (x > y) return ET[mini];
    // Computing minimum in the middle part
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

void init()
{
    preprocessing(1, 1, 0);
    D[N] = INF;
    divide_into_groups();
}
