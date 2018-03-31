// Heavy - Light Decomposition
// Segment tree's operations can be modified
// Complexity:
// 1) Preprocessing: O(|V| + |E|)
// 2) Query about a vertex: O(log |V|)
// 3) Query about a path: O(log^2 |V|)
// Usage: [ONTAK 2017] Remont https://sio2.mimuw.edu.pl/c/wiekuisty_ontak2017/p/rem/
//                     Kontr - zaklęcia https://sio2.mimuw.edu.pl/c/wiekuisty_ontak2017/p/zak/

const int MAXN = 2e5+5;
int sz[MAXN], heavy[MAXN], pre[MAXN], post[MAXN], id[MAXN], par[MAXN], beg[MAXN], Tree[2*1024*1024], Base = 1, tim, nr;
// sz[] - sizes of subrees, heavy[] - child through a heavy edge, pre[] - preorder, post[] - postorder
// id[] - id in segment tree, par[] - parent in the tree, beg[] - highest vertex on a light path
vector<int> G[MAXN]; // Graph

// Computes sz[], par[], heavy[], pre[], post[]
void calcVertices(int v, int p)
{
    sz[v] = 1, par[v] = p, heavy[v] = v, pre[v] = ++tim;
    for (int u : G[v])
    {
        if (u == p) continue;
        calcVertices(u, v);
        if (sz[u] >= sz[heavy[v]]) heavy[v] = u; // Found a child with bigger subtree
        sz[v] += sz[u];
    }
    post[v] = tim;
}

// Computes beg[], id[]
void calcPaths(int v, int p, int d)
{
    for (int u : G[v])
    {
        if (u == p) continue;
        if (heavy[v] == u)
        {
            beg[u] = beg[v];
            calcPaths(u, v, d+1);
        }
        else
        {
            beg[u] = u;
            calcPaths(u, v, 0);
        }
    }
    if (heavy[v] == v) id[v] = nr++;
    else
    {
        id[v] = id[heavy[v]] + 1;
        nr = max(nr, id[v] + d + 1);
    }
}


// Segment tree
void chTree(int node, int left, int right, int l, int r, int v)
{
    if (l <= left && right <= r)
    {
        Tree[node] = v;
        return;
    }
    int mid = (left + right) / 2;
    if (l <= mid) chTree(2*node, left, mid, l, r, v);
    if (mid + 1 <= r) chTree(2*node+1, mid+1, right, l, r, v);
    Tree[node] = Tree[2*node] + Tree[2*node+1];
}

// Segment tree
int read(int node, int left, int right, int l, int r)
{
    if (l <= left && right <= r)
    {
        return Tree[node];
    }

    int mid  = (left + right) / 2, res = 0;
    if (l <= mid) res += read(2*node, left, mid, l, r);
    if (mid+1 <= r) res += read(2*node+1, mid+1, right, l, r);
    return res;
}

int res;
// Goes up the tree until b isn't in a's subtree
int toLCA(int a, int b, bool op)
{
    while (pre[beg[a]] > pre[b] || post[beg[a]] < pre[b])
    {

        if (op) // res = query on a path [ id[a], id[beg[a]] ]
        else // modify a path id[a] --- id[beg[a]]
        a = par[beg[a]];
    }
    return a;
}

// op = 1 -> query, op = 0 -> update
void processQuery(int a, int b, bool op)
{
    res = 0;
    a = toLCA(a, b, op);
    b = toLCA(b, a, op);
    if (id[a] > id[b]) swap(a, b); // lca(a, b) = b;
    if (op) // res = query on a path [ id[a], id[beg[a]] ]
    else  // modify a path id[a] --- id[beg[a]]
}

void init()
{
    preprocessing(1, 1);
    beg[1] = 1;
    hldBuild(1, 1, 0);
}
