// Dynamic lazy segment tree (+, suma)
// Root of the tree manages range [0, Base]
// Can be used instead of segment tree with compression
// Complexity: O(log Base)

int Base = 1024*1024*1024;
// Base = smallest power of 2 >= MAX VALUE

struct Node
{
    Node * l,  * r;
    int sum, lazy, sz;

    Node(int Size) : l(nullptr), r(nullptr), sum(0), lazy(0), sz(Size) {}

    ~Node()
    {
        delete l;
        delete r;
    }

    // Creates left child if it doesn't exist
    Node* L()
    {
        if (l == nullptr) l = new Node(sz / 2);
        return l;
    }

    // Creates right child if it doesn't exist
    Node* R()
    {
        if (r == nullptr) r = new Node(sz / 2);
        return r;
    }

    // Propagation
    void propagate()
    {
        L()->lazy += lazy, L()->sum += lazy * L()->sz;
        R()->lazy += lazy, R()->sum += lazy * R()->sz;
        lazy = 0;
    }

    void chTree(int left, int right, int l, int r, int v)
    {
        if (r < left || right < l) return;
        if (l <= left && right <= r)
        {
            sum += v * sz;
            lazy += v;
            return ;
        }

        propagate();

        int mid = left + right >> 1;
        L()->chTree(left, mid, l, r, v);
        R()->chTree(mid + 1, right, l, r, v);
        sum = L()->sum + R()->sum;
    }

    int read(int left, int right, int l, int r)
    {
        if (r < left || right < l) return 0;
        if (l <= left && right <= r)
        {
            return sum;
        }

        propagate();

        int mid = left + right >> 1;
        return L()->read(left, mid, l, r) + R()->read(mid + 1, right, l, r);
    }
};

// Root
Node * Tree = new Node(Base);
void Query(int l, int r, int v)
{
    if (v) Tree->chTree(0, Base - 1, l, r, v);
    else cout << Tree->read(0, Base - 1, l, r) << "\n";
}
