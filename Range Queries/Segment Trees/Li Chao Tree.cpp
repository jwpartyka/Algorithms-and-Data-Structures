//Li Chao Tree
// 1) Tree[x] = min(Tree[x], ax + b), for x in range [1, n]
// 2) Read Tree[x]
// Complexity: O(log N)

using ll = long long;

const int MAXN = 1e6 + 5;
const ll inf = 1e9;

struct func
{
    ll A, B;

    ll operator / (const func &b) const
    {
        return {A * b.A + B * b.B};
    }
};

int Base = 1;
ll dp[MAXN];
func Tree[2 * 1024 * 1024];

ll f(func a, int x)
{
    func b = {x, 1};
    return a / b;
}

void chTree(int node, int lo, int hi, func v)
{
    int mid = (lo + hi) / 2;
    bool ok1 = f(v, lo) <= f(Tree[node], lo);
    bool ok2 = f(v, mid) <= f(Tree[node], mid);

    if (ok2) swap(Tree[node], v);

    if (hi - lo <= 1) return ;
    else if (ok1 != ok2)
    {
        chTree(2 * node, lo, mid, v);
    }
    else chTree(2 * node + 1, mid + 1, hi, v);
}

ll read(ll x)
{
    ll res = inf * x + inf;
    int node = x + Base;
    do
    {
        res = min(res, Tree[node].A * x + Tree[node].B);
        node /= 2;
    }
    while (node);
    return res;
}
