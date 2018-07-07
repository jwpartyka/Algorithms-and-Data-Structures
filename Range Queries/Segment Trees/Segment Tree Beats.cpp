// Segment tree beats
// Queries:
// 1) Tree[i] = min(Tree[i], x) for i in range [l, r]
// 2) Read a sum over Tree[i] for i in range [l, r]
// Amortized complexity of each query: O(log N)

using ll = long long;

const int MAXN = 3e5 + 5, inf = 1e9;

struct Node
{
    int max1, max2, cnt, lazy;
    ll sum;

    Node operator + (Node b)
    {
        auto a = *this;
        if (a.max1 == b.max1) return {a.max1, max(a.max2, b.max2), a.cnt + b.cnt, inf, a.sum + b.sum};
        if (a.max1 < b.max1) swap(a, b);
        return {a.max1, max(a.max2, b.max1), a.cnt, inf, a.sum + b.sum};
    }
};

int tab[MAXN], Base = 1;
Node Tree[1024 * 1024];

inline void init(int i, int v)
{
    Tree[i + Base] = {v, -inf, 1, inf, v};
}

inline void update(int node, int v)
{
    if (v >= Tree[node].max1) return;
    Tree[node].lazy = min(Tree[node].lazy, v);
    Tree[node].sum -= (ll)(Tree[node].max1 - v) * Tree[node].cnt;
    Tree[node].max1 =  v;
}

inline void propagate(int node)
{
    update(2 * node, Tree[node].lazy);
    update(2 * node + 1, Tree[node].lazy);
    Tree[node].lazy = inf;
}

void build(int node)
{
    if (node >= Base) return;
    build(2 * node);
    build(2 * node + 1);
    Tree[node] = Tree[2 * node] + Tree[2 * node + 1];
}

void chTree(int node, int lo, int hi, int l, int r, int v)
{
    if (r < lo or hi < l) return;
    if  (v >= Tree[node].max1) return;
    if (l <= lo and hi <= r and v > Tree[node].max2)
    {
        update(node, v);
        return;
    }

    propagate(node);
    int mid = lo + hi >> 1;
    chTree(2 * node, lo, mid, l, r, v);
    chTree(2 * node + 1, mid + 1, hi, l, r, v);
    Tree[node] = Tree[2 * node] + Tree[2 * node + 1];
}

ll read(int node, int lo, int hi, int l, int r)
{
    if (r < lo or hi < l) return 0;
    if (l <= lo and hi <= r)
    {
        return Tree[node].sum;
    }

    propagate(node);
    int mid = lo + hi >> 1;
    return read(2 * node, lo, mid, l, r) + read(2 * node + 1, mid + 1, hi, l, r);
}
