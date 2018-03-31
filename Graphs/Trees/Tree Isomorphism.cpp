// Input() read n - 1 edges
// Hash() returns hash of a tree
// To check whether two trees are isomorphic just compare their hashes
// Roots of the trees are their centroids
// Usage: [SPOJ] TREEISO http://www.spoj.com/problems/TREEISO/

#define st first
#define nd second

using ll = long long;

const int MAXN = 1e6+5;

vector<int> val;
int M[MAXN], num = 1;

struct TreeIso
{
    struct hash
    {
        ll a, b, c;
        hash operator + (const ll &v) const
        {
            return {a ^ v, b + v * v, c + v * v * v};
        }
        bool operator == (const hash &B) const
        {
            return (a == B.a && b == B.b && c == B.c);
        }
    };

    vector<int> sz, ID;
    vector<vector<pair<int, int>>> G;
    vector<hash> H;
    int N;

    TreeIso(int n) : N(n), sz(n+3), ID(n+3), G(n+3), H(n+3) {}

    void buildTree()
    {
        for (int i = 1; i < N; i++)
        {
            int a, b;
            cin >> a >> b;
            G[a].push_back({b, G[b].size()});
            G[b].push_back({a, G[a].size()-1});
        }
    }
    void calcSizes(int v, int p)
    {
        sz[v] = 1;
        for (auto e : G[v])
        {
            int u = e.st;
            if (u == p) continue;
            calcSizes(u, v);
            sz[v] += sz[u];
        }
    }

    // Computes hashes of subtress
    void dfs(int v, int p)
    {
        for (auto e : G[v])
        {
            int u = e.st;
            if (u == p) continue;
            dfs(u, v);
            H[v] = H[v] + val[ID[u]];
        }
        ll h = ((H[v].a + H[v].b + H[v].c) % MAXN + MAXN) % MAXN;
        auto &x = M[h];
        if (x == 0)
        {
            x= num;
            ID[v] = num++;
        }
        else ID[v] = x;
    }

    inline void eraseEdge(int v, int i)
    {
        swap(G[v][i], G[v].back());
        G[v].pop_back();
    }

    // Finds centroids of the tree
    pair<int, int> cdFind(int v, int p)
    {
        calcSizes(1, -1);
        int tot = sz[v];
        bool ok = 1;
        while (ok)
        {
            ok = 0;
            for (auto e : G[v])
            {
                int u = e.st, id = e.nd;
                if (u != p && sz[u] * 2 > tot)
                {
                    p = v, v = u, ok = 1;
                    break;
                }
                if (sz[u] * 2 == tot)
                {
                    eraseEdge(v, G[u][id].nd);
                    eraseEdge(u, id);
                    return {v, u};
                }
            }
        }
        return {v, v};
    }

    // Run init() beforehand
    hash Hash()
    {
        auto p = cdFind(1, 1);
        G[0].push_back({p.st, 0});
        G[0].push_back({p.nd, 0});
        dfs(0, -1);
        return H[0];
    }
};

// Run before Hash()
void init()
{
    for (int i = 0; i < MAXN; i++)
    {
        val.push_back(i + 1);
    }
    random_shuffle(val.begin(), val.end());
}
