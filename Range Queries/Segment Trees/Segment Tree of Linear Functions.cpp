// Segment tree of linear functions
// 1) Tree[x] = Tree[x] + (ax + b) for x in range [l, r]
// 2) Get sum of Tree[i] for i in range [l, r]
// Usage: [XXV POI] 

using ll = long long;

struct func
{
    ll A, B;

    func operator + (const func &b) const
    {
        return {A + b.A, B + b.B};
    }

    func operator * (const func &b) const
    {
        return {A * b.A, B * b.B};
    }
};

struct Node
{
    func res, lazy;
};

int Base = 1;
Node Tree[2 * 1024 * 1024];

ll f(ll x)
{
    return (x * x + x) / 2;
}

ll sum(int a, int b)
{
    return f(b) - f(a - 1);
}

inline void propagate(int node, int lo, int hi)
{
    if (Tree[node].lazy.A == 0 && Tree[node].lazy.B == 0) return ;

    int mid = (lo + hi) / 2, sz = (hi - lo + 1) / 2;
    func x = {sum(lo, mid), sz};
    for (int i = 2 * node; i <= 2 * node + 1; i++)
    {
        Tree[i].res = Tree[i].res + (Tree[node].lazy * x);
        Tree[i].lazy = Tree[i].lazy + Tree[node].lazy;
        x.A = sum(mid + 1, hi);
    }
    Tree[node].lazy = {0, 0};
}

void chTree(int node, int lo, int hi, int l, int r, func v)
{
    if (r < lo || hi < l) return ;
    if (l <= lo && hi <= r)
    {
        func x = {sum(lo, hi), hi - lo + 1};
        Tree[node].res = Tree[node].res + (v * x);
        Tree[node].lazy = Tree[node].lazy + v;
        return ;
    }

    propagate(node, lo, hi);

    int mid = (lo + hi) / 2;
    chTree(2 * node, lo, mid, l, r, v);
    chTree(2 * node + 1, mid + 1, hi, l, r, v);

    Tree[node].res = Tree[2 * node].res + Tree[2 * node + 1].res;
}

func read(int node, int lo, int hi, int l, int r)
{
    if (r < lo || hi < l) return {0, 0};
    if (l <= lo && hi <= r)
    {
        return Tree[node].res;
    }

    propagate(node, lo, hi);

    int mid = (lo + hi) / 2;
    return read(2 * node, lo, mid, l, r) +
            read(2 * node + 1, mid + 1, hi, l, r);
}

inline void query(int l, int r, int A, int B)
{
    chTree(1, 0, Base - 1, l, r, {A, B});
}
