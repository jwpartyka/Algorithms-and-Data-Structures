// Persistent segment tree using pointers
// Builds full binary tree even if not every node will be used
// Slower and uses more memory then the version using array
// Usage: http://www.spoj.com/problems/PSEGTREE/

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

    // Creates and returns a pointer to the left child
    Node * L()
    {
        l = new Node();
        return l;
    }

    // Creates and returns a pointer to the right child
    Node * R()
    {
        r = new Node();
        return r;
    }

    // Fills the original tree in linear time
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

    // Adds a new version of a path to the tree
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

    // Reads sum over a segment [l, r]
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

vector<Node *> Tree; // List of ids of roots of new versions of the tree

// Creates a new root
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
