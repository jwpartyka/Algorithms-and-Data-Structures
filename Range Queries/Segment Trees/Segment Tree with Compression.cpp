// Lazy Segment tree (+, sum) with data compression.
// Real leafs have numbers 2 * k and imaginary leafs have 2 * k + 1
// We create imaginary leafs for convenience. They're just empty nodes which won't
// ever be modified. They help keep the correct subtrees sizes and values in the tree.

#define st first
#define nd second

const int MAXN = 5e5+5;

struct Node
{
    int res, lazy, sz, og;
};

Node Tree[2*1024*1024];
int que[MAXN][4], Base = 1;
map<int, int> sc;

// Computes the actual sizes of subtrees
void calcSizes(int node)
{
    if (node >= Base) return ;
    calcSizes(2*node), calcSizes(2*node+1);
    Tree[node].sz = Tree[2*node].sz + Tree[2*node+1].sz;
}

void zepchnij(int node)
{
    for (int i = 2*node; i <= 2*node+1; i++)
    {
        Tree[i].res += Tree[i].sz * Tree[node].lazy;
        Tree[i].lazy += Tree[node].lazy;
    }
    Tree[node].lazy = 0;
}

void chTree(int node, int left, int right, int l, int r, int v)
{
    if (r < left || right < l) return ;
    if (l <= left && right <= r)
    {
        Tree[node].res += Tree[node].sz * v;
        Tree[node].lazy += v;
        return ;
    }

    zepchnij(node);

    int mid = left + right >> 1;
    chTree(2*node, left, mid, l, r, v);
    chTree(2*node+1, mid+1, right, l, r, v);
    Tree[node].res = Tree[2*node].res + Tree[2*node+1].res;
}

int read(int node, int left, int right, int l, int r)
{
    if (r < left || right < l) return 0;
    if (l <= left && right <= r)
    {
        return Tree[node].res;
    }

    zepchnij(node);

    int mid = left + right >> 1;
    return read(2*node, left, mid, l, r) + read(2*node+1, mid+1, right, l, r);
}

// Compresses queries and creates imaginary leafs
void compress()
{
    while (Base < 2 * sc.size() - 1) Base *= 2;
    int nr = 0;
    for (auto &v : sc)
    {
        Tree[nr+Base].og = v.st;
        Tree[nr+Base].sz = 1;
        v.nd = nr;
        nr += 2;
    }
    for (int i = 1; i < nr-2; i += 2)
    {
        Tree[i+Base].og = Tree[Base+i+1].og - 1;
        Tree[i+Base].sz = Tree[i+Base].og - Tree[i+Base-1].og;
    }
    calcSizes(1);
}

// Example of usage:
// Reads queries, compresses queries, answers queries
int main()
{
    int q;
    cin >> q;
    for (int i = 0; i < q; i++)
    {
        cin >> que[i][0];
        if (que[i][0] == 1)
        {
            for (int j = 1; j <= 2; j++)
            {
                cin >> que[i][j];
                sc[que[i][j]];
            }
            cin >> que[i][3];
        }
        else
        {
            for (int j = 1; j <= 2; j++)
            {
                cin >> que[i][j];
                sc[que[i][j]];
            }
        }
    }

    compress();

    for (int i = 0; i < q; i++)
    {
        if(que[i][0] == 1)
        {
            chTree(1, 0, Base-1, sc[que[i][1]], sc[que[i][2]], que[i][3]);
        }
        else cout << read(1, 0, Base-1, sc[que[i][1]], sc[que[i][2]]) << "\n";
    }
}
