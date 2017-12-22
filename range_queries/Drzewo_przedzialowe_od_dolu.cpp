//Drzewo przedziałowe (+, suma) od dołu

const int MAXN = 1e5+5;

int Tree[2*1024*1024], Base = 1;

void treeBuild(int node)
{
    if (node >= Base) return;
    treeBuild(2*node), treeBuild(2*node+1);
    Tree[node] = Tree[2*node] + Tree[2*node+1];
}

//Wersja punkt-przedział:
void chTree(int node, int v)
{
    node += Base - 1;
    Tree[node] += v;
    node /= 2;
    while (node)
    {
        Tree[node] += v;
        node /= 2;
    }
}

int read(int l, int r)
{
    l += Base - 1, r += Base - 1;
    int res = Tree[l];
    if (l != r)
    {
        res += Tree[r];
    }
    while (l / 2 != r / 2)
    {
        if (l%2 == 0)
        {
            res += Tree[l+1];
        }
        if (r%2 == 1)
        {
            res += Tree[r-1];
        }
        l /= 2, r /= 2;
    }
    return res;
}

//Wersja przedział-punkt:
void chTree(int l, int r, int v)
{
    l += Base - 1, r += Base - 1;
    Tree[l] += v;
    if (l != r)
    {
        Tree[r] += v;
    }
    while (l / 2 != r / 2)
    {
        if (l%2 == 0)
        {
            Tree[l + 1] += v;
        }
        if (r%2 == 1)
        {
            Tree[r - 1] += v;
        }
        l /= 2;
        r /= 2;
    }
}

int read(int node)
{
    int res = 0;
    while (node)
    {
        res += Tree[node];
        node /= 2;
    }
    return res;
}
