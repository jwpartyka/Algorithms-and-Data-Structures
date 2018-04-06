// Wavelet tree
// Queries:
// 1) Count numbers equal to k in range [a, b] -> (cntK(b, k) - cntK(a - 1, k))
// 2) Count numbers that are less than or equal to k in range [a, b] -> (LTE(b, k) - LTE(a - 1, k))
// 3) Count numbers from range [x, y] in range [a, b]
// 4) Kth smallest value in range [a, b]
// 5) Index of the lth occurrence of the kth smallest number on prefix [1, i] -> kthPos(i, k, l)
// 6) Swap elements at indices i and i + 1 -> swap(i)
// Modyfing the sequence requires rebuilding the entire tree.
// Complexity:
// 1) Preprocessing: O(N)
// 2) Query: O(log N)

const int MAXN = 3e5 + 5, inf = 1e9;

int tab[MAXN];
map<int, int> sc;

struct Wavelet
{
    Wavelet * left, * right;
    int lo, hi;
    vector<int> seq, ML;

    Wavelet(int lo, int hi) : lo(lo), hi(hi), left(nullptr), right(nullptr) {}

    void init(int n)
    {
        for (int i = 1; i <= n; i++)
        {
            seq.push_back(i);
        }
    }

    void build()
    {
        if (lo == hi) return ;

        int mid = lo + hi >> 1;
        left = new Wavelet(lo, mid);
        right = new Wavelet(mid + 1, hi);

        ML.push_back(0);
        for (int i : seq)
        {
            ML.push_back(ML.back());
            if (tab[i] <= mid)
            {
                left -> seq.push_back(i);
                ML.back()++;
            }
            else right -> seq.push_back(i);
        }

        if (left -> seq.size()) left -> build();
        if (right -> seq.size()) right -> build();
        seq.clear();
    }

    // Counts numbers equal to k on prefix [1, b]
    int cntK(int b, int k)
    {
        if (b <= 0) return 0;
        if (lo == hi)
        {
            if (lo != k) return 0;
            return b;
        }

        int mid = lo + hi >> 1;
        if (k <= mid) return left -> cntK(ML[b], k);
        return right -> cntK(b - ML[b], k);
    }

    // Counts numbers that are less than of equal to k on prefix [1, b]
    int LTE(int b, int k)
    {
        if (b <= 0) return 0;
        if (lo == hi)
        {
            if (lo <= k) return b;
            return 0;
        }

        int mid = lo + hi >> 1;
        if (k <= mid) return left -> LTE(ML[b], k);
        return ML[b] + right -> LTE(b - ML[b], k);
    }

    // Counts numbers from range [x, y] in range [a, b]
    int cntFromXtoY(int a, int b, int x, int y)
    {
        return LTE(b, y) - LTE(a - 1, y) - LTE(b, x - 1) + LTE(a - 1, x - 1);
    }

    // Kth smallest number in range [a, b]
    int kth(int a, int b, int k)
    {
        if (lo == hi) return lo;

        int x = ML[b] - ML[a - 1];
        if (x >= k) return left -> kth(ML[a - 1] + 1, ML[b], k);
        return right -> kth(a - ML[a - 1], b - ML[b], k - x);
    }

    // Updates the sequence after swap() splits into to subtrees
    void swapUpdate(int i, int j)
    {
        seq[i - 1] = j;
        if (lo == hi) return ;

        int mid = lo + hi >> 1;
        if (tab[j] <= mid) left -> swapUpdate(ML[i], j);
        else right -> swapUpdate(i - ML[i], j);
    }

    // Swaps values on positions i and i + 1
    void swap(int i)
    {
        if (lo == hi) return ;

        if (ML[i] > ML[i - 1] && ML[i + 1] > ML[i]) left -> swap(ML[i]);
        else if (ML[i] == ML[i - 1] && ML[i + 1] == ML[i]) right -> swap(i - ML[i]);
        else
        {
            if (ML[i] > ML[i - 1])
            {
                ML[i]--;
                left -> swapUpdate(ML[i + 1], seq[i]);
                right -> swapUpdate(i - ML[i], seq[i - 1]);
            }
            else
            {
                ML[i]++;
                left -> swapUpdate(ML[i], seq[i - 1]);
                right -> swapUpdate(i + 1 - ML[i], seq[i]);
            }
        }
    }


    // Index of the lth occurrence of the kth smallest number on prefix [1, i]
    int kthPos(int i, int k, int l)
    {
        if (lo == hi)
        {
            if (l > seq.size()) return -1;
            return seq[l - 1] - 1;
        }

        if (ML[i] >= k) return left -> kthPos(ML[i], k, l);
        return right -> kthPos(i - ML[i], k - ML[i], l);
    }
};

void compress(int n)
{
    for (int i = 1; i <= n; i++)
    {
        sc[tab[i]];
        sc[i];
    }

    int num = 1;
    for (auto &v : sc)
    {
        v.second = num++;
    }

    for (int i = 1; i <= n; i++)
    {
        tab[i] = sc[tab[i]];
    }
}

Wavelet * Tree;
void init(int n)
{
    //compress(n);
    Tree = new Wavelet(1, /*sc.size()*/ inf);
    Tree -> init(n);
    Tree -> build();
}
