//Drzewo trwałe (na tablicy)
//Kod to rozwiązanie zadania: http://www.spoj.com/problems/PSEGTREE/
//Kod ma w miarę dożyłowaną pamięć i czas

#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 1e5 + 5;

struct Node
{
    int l, r, sum;
};


int Base = 1, num = 0, n;
vector<int> roots, tab;
vector<Node> Tree;

int buildTree(int node, int lo, int hi)
{
    if (lo > n) return 0;

    num++;
    if (lo == hi)
    {
        Tree[node].sum = tab[lo];
        return node;
    }

    int mid = (lo + hi) / 2;
    Tree[node].l = buildTree(num + 1, lo, mid);
    Tree[node].r = buildTree(num + 1, mid + 1, hi);

    Tree[node].sum = Tree[Tree[node].l].sum + Tree[Tree[node].r].sum;
    return node;
}

int chTree(int node, int lo, int hi, int N, int v)
{
    if (N < lo || hi < N || !node) return node;

    num++;
    if (lo == hi)
    {
        Tree[num].sum = Tree[node].sum + v;
        return num++;
    }

    int mid = (lo + hi) / 2;
    int id = num;
    Tree[id].l = chTree(Tree[node].l, lo, mid, N, v);
    Tree[id].r = chTree(Tree[node].r, mid + 1, hi, N, v);

    Tree[id].sum = Tree[Tree[id].l].sum + Tree[Tree[id].r].sum;
    return id;
}

int read(int node, int lo, int hi, int l, int r)
{
    if (r < lo || hi < l) return 0;
    if (l <= lo && hi <= r)
    {
        return Tree[node].sum;
    }

    int mid = (lo + hi) / 2;
    return read(Tree[node].l, lo, mid, l, r) +
            read(Tree[node].r, mid + 1, hi, l, r);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    tab.resize(n + 3);
    Tree.resize(n * 18);
    while (Base < n) Base *= 2;

    for (int i = 1; i <= n; i++)
    {
        cin >> tab[i];
    }

    roots.push_back(1);
    buildTree(1, 1, Base);

    int q;
    cin >> q;
    while (q--)
    {
        int co;
        cin >> co;
        if (co - 1)
        {
            int id, l, r;
            cin >> id >> l >> r;
            cout << read(roots[id], 1, Base, l, r) << "\n";
        }
        else
        {
            int id, pos, v;
            cin >> id >> pos >> v;
            roots.push_back(num + 1);
            chTree(roots[id], 1, Base, pos, v);
        }
    }
}
