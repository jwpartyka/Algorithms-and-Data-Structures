//Wavelet Tree
//Udostępnia zapytania:
//1) Liczba wystąpień liczby k na przedziale [a, b] -> (cntK(b, k) - cntK(a - 1, k))
//2) Ile liczba mniejszych / równych k na przedziale [a, b] -> (LTE(b, k) - LTE(a - 1, k))
//3) Ile liczb z przedziału [x, y] na przedziale [a, b]
//4) K-ty najmniejszy element na przedziale [a, b]
//5) Pozycja l-tego wystąpienia k-tego najmniejszego elementu na prefiksie [1, i] -> kthPos(i, k, l)
//6) Swap elementów na pozycjach i oraz i + 1 -> swap(i)

//Nie można aktualizować wartości w ciągu
//Złożoność zapytania: O(log N)

const int MAXN = 1e6+5;

int tab[MAXN];

struct Wavelet
{
    Wavelet * left, * right;
    int l, r;
    vector<int> seq, ML;

    Wavelet(int l, int r) : l(l), r(r), left(nullptr), right(nullptr) {}

    void init(int n)
    {
        for (int i = 1; i <= n; i++)
        {
            seq.push_back(i);
        }
    }

    void build()
    {
        if (l == r) return ;
        int mid = (l + r) / 2;
        left = new Wavelet(l, mid);
        right = new Wavelet(mid + 1, r);
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

    //Ile liczb równych k na prefiksie [1, b]
    int cntK(int b, int k)
    {
        if (b <= 0) return 0;
        if (l == r)
        {
            if (l != k) return 0;
            return b;
        }
        int mid = (l + r) / 2;
        if (k <= mid) return left -> cntK(ML[b], k);
        return right -> cntK(b - ML[b], k);
    }

    //Ile liczb mniejszych niż lub równych k na prefiksie [1, b]
    int LTE(int b, int k)
    {
        if (b <= 0) return 0;
        if (l == r)
        {
            if (l <= k) return b;
            return 0;
        }
        int mid = (l + r) / 2;
        if (k <= mid) return left -> LTE(ML[b], k);
        return ML[b] + right -> LTE(b - ML[b], k);
    }

    //Ile liczb z przedziału [x, y] na przedziale [a, b]
    int cntFromXtoY(int a, int b, int x, int y)
    {
        return LTE(b, y) - LTE(a - 1, y) - LTE(b, x - 1) + LTE(a - 1, x - 1);
    }

    //K-ta najmniejsza wartość na przedziale [a, b]
    int kth(int a, int b, int k)
    {
        if (l == r) return l;
        int x = ML[b] - ML[a - 1];
        if (x >= k) return left -> kth(ML[a - 1] + 1, ML[b], k);
        return right -> kth(a - ML[a - 1], b - ML[b], k - x);
    }

    //Aktualizacja ciągu po rozdzieleniu się na dwóch synów w funkcji swap
    void swapUpdate(int i, int j)
    {
        seq[i - 1] = j;
        if (lo == hi) return ;
        int mid = (lo + hi) / 2;
        if (tab[j] <= mid) left -> swapUpdate(ML[i], j);
        else right -> swapUpdate(i - ML[i], j);
    }

    //Zamiana wartości na pozycjach i oraz i + 1
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

    //Pozycja l-tego wystąpienia k-tej najmniejszej wartości na prefiksie [1, i]
    int kthPos(int i,  int  k, int l)
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

Wavelet * Wave = new Wavelet(1, MAXN);
void przygotuj(int n)
{
    Wave -> init(n);
    Wave -> build();
}
