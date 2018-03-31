// Knapsack problem
// Complexity: O(N ^ 2)
// Usage: [SPOJ] KNAPSACK http://www.spoj.com/problems/KNAPSACK/

const int MAXN = 1e3+5;

struct Item
{
    int w, c; //weight and cost of an item
    bool operator < (const Item &b) const
    {
        if (w == b.w) return c < b.c;
        return w < b.w;
    }
};

Item item[MAXN];
int sack[MAXN];

int knapsack(int n, int k)
{
    sort(item, item  + n);
    for (int i = 0; i < n; i++)
    {
        for (int j = k - item[i].w; j >= 0; j--)
        {
            if (sack[j] || j == 0)
            {
                sack[j + item[i].w] = max(sack[j + item[i].w], sack[j] + item[i].c);
            }
        }
    }

    int res = 0;
    for (int i = 1; i <= k; i++)
    {
        res = max(res, sack[i]);
    }
    return res;
}
