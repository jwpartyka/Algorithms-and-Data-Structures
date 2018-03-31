// Segment tree beats
// Queries:
// 1) Tree[i] = min(Tree[i], x) for i in range [l, r]
// 2) Read a sum over Tree[i] for i in range [l, r]
// Amortized complexity of each query: O(log N)

using ll = long long;

const int MAXN = 3e5 + 5, inf = 1e9 + 7;

struct Node
{
    int max1, max2, cnt, lazy;
    ll sum;
    Node operator + (const Node &B) const
    {
        Node N;
        if (max1 >= B.max1) N = *this;
        else N = B;
        N.sum = sum + B.sum;
        if (max1 == B.max1)
        {
            N.cnt += B.cnt;
            N.max2 = max(max2, B.max2);
        }
        else if (max1 > B.max1) N.max2 = max(max2, B.max1);
        else N.max2 = max(max1, B.max2);
        return N;
    }

    inline void init(int v)
    {
        max1 = sum = lazy = v;
        max2 = 0;
        cnt = 1;
    }
};

int tab[MAXN], Base = 1;
Node Tree[2*512*1024];

inline void update(int node)
{
    Tree[node] = Tree[2*node] + Tree[2*node+1];
}

void build(int node)
{
    if (node >= Base) return;
    build(2*node), build(2*node+1);
    update(node);
}

void minuj(int node, int v)
{
    if (v >= Tree[node].max1) return;
    Tree[node].lazy = min(Tree[node].lazy, v);
    if (v >= Tree[node].max2)
    {
        Tree[node].sum -= (ll)(Tree[node].max1 - v) * Tree[node].cnt;
        Tree[node].max1 = v;
    }
    if (v <= Tree[node].max2)
    {
        minuj(2 * node, v);
        minuj(2 * node + 1, v);
        update(node);
    }
}

inline void propaguj(int node)
{
    for (int i = 2*node; i <= 2*node+1; i++)
    {
        Tree[i].lazy = min(Tree[i].lazy, Tree[node].lazy);
        minuj(i, Tree[i].lazy);
    }
}

void chTree(int node, int left, int right, int l, int r, int v)
{
    if (right < l || r < left) return;
    if (l <= left && right <= r)
    {
        minuj(node, v);
        return;
    }
    propaguj(node);
    int mid = (left + right) / 2;
    chTree(2 * node, left, mid, l, r, v);
    chTree(2 * node + 1, mid + 1, right, l, r, v);
    update(node);
}

ll read(int node, int left, int right, int l, int r)
{
    if (right < l || r < left) return 0;
    if (l <= left && right <= r)
    {
        return Tree[node].sum;
    }
    propaguj(node);
    int mid = (left + right) / 2;
    return read(2 * node, left, mid, l, r) +
        +  read(2 * node + 1, mid + 1, right, l, r);
}
