//Drzewo przedziałowe przedział-przedział (+, suma)

#define mid (left+right)/2 //środek przedziału w drzewie przedziałowym

const int MAXN = 1e5+5;
struct Node
{
    int res, lazy, sz;
};

Node Tree[2*1024*1024];
int Base = 1;

void treeBuild(int node)
{
    if (node >= Base)
    {
        Tree[node].sz = 1;
        return;
    }
    treeBuild(2*node);
    treeBuild(2*node+1);
    Tree[node].res = Tree[2*node].res + Tree[2*node+1].res;
    Tree[node].sz = Tree[2*node].sz + Tree[2*node+1].sz;
}

void zepchnij(int node)
{
    if (!Tree[node].lazy) return;
    for (int i = 2*node; i <= 2*node+1; i++)
    {
        Tree[i].res += Tree[node].lazy * Tree[i].sz;
        Tree[i].lazy += Tree[node].lazy;
    }
    Tree[node].lazy = 0;
}

void chTree(int node, int left, int right, int l, int r, int v)
{
    if (r < left || right < l) return;
    if (l <= left && right <= r)
    {
        Tree[node].lazy += v;
        Tree[node].res += Tree[node].sz * v;
        return ;
    }
    zepchnij(node);
    chTree(2*node, left, mid, l, r, v);
    chTree(2*node+1, mid + 1, right, l, r, v);
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
    return read(2*node, left, mid, l, r) +
            read(2*node+1, mid + 1, right, l, r);
}

int readArray(int n)
{
    while (Base < n) Base *= 2;
    for (int i = 0; i < n; i++)
    {
        int v;
        cin >> v;
        Tree[i + Base].res += v;
    }
    treeBuild(1);
}
