// Computes minimum in a range [l, r] in constant time (after preprocessing)
// Time complexity:
// 1) Preprocessing: O(N * log N)
// 2) Query: O(1)
// Memory complexity: O(N * log N)

const int MAXN = 5e5+5, LOG = 20;

// Array with original values, Sprase Table for tab array
int tab[MAXN], ST[MAXN][LOG+3];

void calcST(int n)
{
    for (int i = 0; i < n; i++)
    {
        ST[i][0] = tab[i];
    }
    for (int j = 1; (1<<j) <= n; j++)
    {
        for (int i = 0; i + (1<<j) - 1 < n; i++)
        {
            ST[i][j] = min(ST[i][j-1], ST[i + (1<<(j-1))][j-1]);
        }
    }
}

int minimum(int l, int r)
{
    if (l == r) return tab[l];
    int x = 31 - __builtin_clz(r-l+1);
    return min(ST[l][x], ST[r - (1<<x) + 1][x]);
}
