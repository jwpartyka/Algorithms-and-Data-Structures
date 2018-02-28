//Drzewo trwałe (na wskaźnikach)
//Rozwiązuje zadanie: http://www.spoj.com/problems/PSEGTREE/
//Zużywa więcej czasu i pamięci niż analogiczna wersja na tablicy.
//Buduje pełne drzewo binarne nawet jeżeli nie wszystkie liście zostaną użyte.

#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 5e5 + 5;

int tab[MAXN], Base = 1;

struct Node
{
    Node * l, * r;
    int sum;

    Node() : l(nullptr), r(nullptr), sum(0) {}

    ~Node()
    {
        delete l;
        delete r;
    }

    //Tworzy i zwraca wskaźnik na lewego syna:
    Node * L()
    {
        l = new Node();
        return l;
    }

    //Tworzy i zwraca wskaźnik na prawego syna:
    Node * R()
    {
        r = new Node();
        return r;
    }

    //Uzupełnia wartości w wierzchołkach pierwotnego drzewa przedziałowego:
    void buildTree(int lo, int hi)
    {
        if (lo == hi)
        {
            sum = tab[lo];
            return ;
        }

        int mid = lo + hi >> 1;
        L() -> buildTree(lo, mid);
        R() -> buildTree(mid + 1, hi);
        sum = l -> sum + r -> sum;
    }

    //Dodaje do drzewa nową wersję ścieżki:
    Node * chTree(Node * node, int lo, int hi, int N, int v)
    {
        if (N < lo || hi < N) return node;
        if (lo == hi)
        {
            sum = node -> sum + v;
            return this;
        }

        int mid = lo + hi >> 1;
        l = L() -> chTree(node -> l, lo, mid, N, v);
        r = R() -> chTree(node -> r, mid + 1, hi, N, v);
        sum = l -> sum + r -> sum;
        return this;
    }

    //Zczytuje sumę z przedziału [l, r]:
    int read(int lo, int hi, int left, int right)
    {
        if (right < lo || hi < left) return 0;
        if (left <= lo && hi <= right)
        {
            return sum;
        }

        int mid = lo + hi >> 1;
        return l -> read(lo, mid, left, right) +
                r -> read(mid + 1, hi, left, right);
    }
};

vector<Node *> Tree; //Lista korzeni kolejnych wersji drzewa

//Tworzy korzeń drzewa:
void newTree()
{
    Tree.push_back(new Node());
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    while (Base < n) Base <<= 1;

    for (int i = 1; i <= n; i++)
    {
        cin >> tab[i];
    }

    newTree();
    Tree[0] -> buildTree(1, Base);

    int q;
    cin >> q;
    int num = 0;
    while (q--)
    {
        int co;
        cin >> co;
        if (co == 1)
        {
            int id, pos, v;
            cin >> id >> pos >> v;
            newTree();
            num++;
            Tree[num] -> chTree(Tree[id], 1, Base, pos, v);
        }
        else
        {
            int id, l, r;
            cin >> id >> l >> r;
            cout << Tree[id] -> read(1, Base, l, r) << "\n";
        }
    }
}
