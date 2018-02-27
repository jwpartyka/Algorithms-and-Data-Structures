//Drzewo trwałe (na wskaźnikach)
//Kod to rozwiązanie zadania: http://www.spoj.com/problems/PSEGTREE/
//Zużywa dużo pamięci i czasu

#include <iostream>

using namespace std;

const int MAXN = 1e5 + 5, INF = 1024*256;

int tab[MAXN], Base = 1, n;

struct Node
{
    Node * l, * r;
    int sum, lo, hi;

    Node(int lo, int hi) : sum(0), lo(lo), hi(hi), l(nullptr), r(nullptr) {}

    ~Node()
    {
        delete l;
        delete r;
    }

    void init()
    {
        if (lo > n) return ;
        if (lo == hi)
        {
            sum = tab[lo];
            return ;
        }
        int mid = (lo + hi) / 2;
        L() -> init();
        R() -> init();
        sum = l -> sum + r -> sum;
    }

    Node * L()
    {
        if (l == nullptr) l = new Node(lo, (lo + hi) / 2);
        return l;
    }

    Node * R()
    {
        if (r == nullptr)  r = new Node((lo + hi) / 2 + 1, hi);
        return r;
    }

    Node * chTree(int N, int v, Node * prev)
    {
        if (N < lo || hi < N) return prev;
        if (lo == hi)
        {
            sum = prev -> sum + v;
            return this;
        }

        l = L() -> chTree(N, v, prev -> l);
        r = R() -> chTree(N, v, prev -> r);
        sum = l -> sum + r -> sum;
        return this;
    }

    int read(int left, int right)
    {
        if (right < lo || hi < left) return 0;
        if (left <= lo && hi <= right)
        {
            return sum;
        }

        return l -> read(left, right) + r -> read(left, right);
    }

    void display()
    {
        if (l != nullptr) L() -> display();
        cout << lo << " " << hi << " " << sum << "\n";
        if (r != nullptr) R() -> display();
    }
};

Node * Tree[MAXN];
void init(int x)
{
    Tree[x] = new Node(1, Base);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    while (Base < n) Base *= 2;
    init(0);
    for (int i = 1; i <= n; i++)
    {
        cin >> tab[i];
    }

    Tree[0] -> init();

    int q;
    cin >> q;
    int nr = 1;
    for (int i = 0; i < q; i++)
    {
        int co;
        cin >> co;
        if (co == 2)
        {
            int id, l, r;
            cin >> id >> l >> r;
            cout << Tree[id] -> read(l, r) << "\n";
        }
        else
        {
            int id, pos, v;
            cin >> id >> pos >> v;
            init(nr);
            Tree[nr] -> chTree(pos, v, Tree[id]);
            nr++;
        }
    }
}
