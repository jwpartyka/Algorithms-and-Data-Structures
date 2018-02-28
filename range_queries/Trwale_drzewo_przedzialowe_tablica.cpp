//Drzewo trwałe (na tablicy)
//Rozwiązuje zadanie: http://www.spoj.com/problems/PSEGTREE/
//Buduje pełne drzewo binarne nawet jeżeli nie wszystkie liście zostaną użyte.
//Pierwotne drzewo ma standardową numerację wierzchołków drzewa przedziałowego,
//a wierzchołki na dodawanych ścieżkach przyjmują kolejne niewykorzystane numery.

#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 5e5 + 5, LOG = 20;

struct Node
{
    int l, r, sum;
};

int Base = 1, num;
Node Tree[LOG * MAXN];
vector<int> root; //Lista numerów korzeni kolejnych wersji drzewa

//Uzupełnia wartości w wierzchołkach pierwotnego drzewa przedziałowego:
int buildTree(int node, int lo, int hi)
{
    if (lo != hi)
    {
        int mid = lo + hi >> 1;
        Tree[node].l = buildTree(2 * node, lo, mid);
        Tree[node].r = buildTree(2 * node + 1, mid + 1, hi);
        Tree[node].sum = Tree[2 * node].sum + Tree[2 * node + 1].sum;
    }
    return node;
}

//Dodaje do drzewa nową wersję ścieżki
int chTree(int node, int lo, int hi, int N, int v)
{
    if (N < lo || hi < N) return node;
    num++;
    if (lo == hi)
    {
        Tree[num].sum = Tree[node].sum + v;
        return num;
    }

    int id = num, mid = lo + hi >> 1;
    Tree[id].l = chTree(Tree[node].l, lo, mid, N, v);
    Tree[id].r = chTree(Tree[node].r, mid + 1, hi, N, v);
    Tree[id].sum = Tree[ Tree[id].l ].sum +  Tree[ Tree[id].r ].sum;
    return id;
}

//Zczytuje sumę z przedziału [l, r]
int read(int node, int lo, int hi, int l, int r)
{
    if (r < lo || hi < l) return 0;
    if (l <= lo && hi <= r)
    {
        return Tree[node].sum;
    }

    int mid = lo + hi >> 1;
    return read(Tree[node].l, lo, mid, l, r) +
            read(Tree[node].r, mid + 1, hi, l, r);
}


int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    while (Base < n) Base <<= 1;
    num = Base << 1;

    for (int i = 0; i < n; i++)
    {
        cin >> Tree[Base + i].sum;
    }

    root.push_back(1);
    buildTree(1, 1, Base);

    int q;
    cin >> q;
    while (q--)
    {
        int co;
        cin >> co;
        if (co == 1)
        {
            int id, pos, v;
            cin >> id >> pos >> v;
            root.push_back(num + 1);
            chTree(root[id], 1, Base, pos, v);
        }
        else
        {
            int id, l, r;
            cin >> id >> l >> r;
            cout << read(root[id], 1, Base, l, r) << "\n";
        }
    }
}
