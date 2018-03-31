// Fenwick Tree (+, sum)
// Query complexity: O(log Base)

int Tree[2*1024*1024], Base = 1;

int f(int x)
{
    return x & (-x);
}

void chTree(int node, int v)
{
    while (node <= Base)
    {
        Tree[node] += v;
        node += f(node);
    }
}

int read(int node)
{
    if (node < 0) return 0;
    int res = 0;
    while (node)
    {
        res += Tree[node];
        node -= f(node);
    }
    return res;
}
