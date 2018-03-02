//Drzewo przedziałowe 2D: ustaw wartość w punkcie (x, y), zczytaj gcd z prostokąta.
//Rozwiązuje zadanie: https://wcipeg.com/problem/ioi1323
//Złożoność zapytania: O(log^2(n))

using ll = long long;

//Podstawa zewnętrznego / wewnętrznego drzewa:
int BaseX = 1, BaseY = 1;

//Wierzchołek wewnętrznego drzewa przedziałowego:
struct NodeY
{
    NodeY * left, * right;
    ll gcd;

    NodeY() : left(nullptr), right(nullptr), gcd(0) {}

    ~NodeY()
    {
        delete left;
        delete right;
    }

    NodeY * L()
    {
        if (left == nullptr) left = new NodeY();
        return left;
    }

    NodeY * R()
    {
        if (right == nullptr) right = new NodeY();
        return right;
    }

    //Aktualizowanie wartości w drzewie przedziałowym:
    void update(NodeY * node1, NodeY * node2, int lo, int hi, int N)
    {
        if (N < lo || hi < N) return ;
        if (lo == hi)
        {
            gcd = __gcd(node1 -> gcd, node2 -> gcd);
            return ;
        }

        int mid = (lo + hi) >> 1;
        L() -> update(node1 -> L(), node2 -> L(), lo, mid, N);
        R() -> update(node1 -> R(), node2 -> R(), mid + 1, hi, N);
        gcd = __gcd(L() -> gcd, R() -> gcd);
    }

    //Ustawianie wartości v w punkcie N:
    void chTree(int lo, int hi, int N, ll v)
    {
        if (N < lo || hi < N) return ;
        if (lo == hi)
        {
            gcd = v;
            return ;
        }

        int mid = (lo + hi) >> 1;
        L() -> chTree(lo, mid, N, v);
        R() -> chTree(mid + 1, hi, N, v);
        gcd = __gcd(L() -> gcd, R() -> gcd);
    }

    //Zczytywanie gcd z przedziału [l, r]:
    ll read(int lo, int hi, int l, int r)
    {
        if (r < lo || hi < l) return 0;
        if (l <= lo && hi <= r)
        {
            return gcd;
        }

        int mid = (lo + hi) >> 1;
        return __gcd(L() -> read(lo, mid, l, r),
                     R() -> read(mid + 1, hi, l, r));
    }
};

struct NodeX
{
    NodeX * left, * right;
    NodeY * Tree;

    NodeX() : left(nullptr), right(nullptr), Tree(nullptr) {}

    ~NodeX()
    {
        delete left;
        delete right;
        delete Tree;
    }

    NodeX * L()
    {
        if (left == nullptr) left = new NodeX();
        return left;
    }

    NodeX * R()
    {
        if (right == nullptr) right = new NodeX();
        return right;
    }

    NodeY * T()
    {
        if (Tree == nullptr) Tree =  new NodeY();
        return Tree;
    }

    //Ustawianie wartości v w punkcie (NX, NY)
    void chTree(int lo, int hi, int NX, int NY, ll v)
    {
        if (NX < lo || hi < NX) return ;
        if (lo == hi)
        {
            T() -> chTree(1, BaseY, NY, v);
            return ;
        }

        int mid = (lo + hi) >> 1;
        L() -> chTree(lo, mid, NX, NY, v);
        R() -> chTree(mid + 1, hi, NX, NY, v);
        //Zaktualizowanie drzew przedziałowych w przedziałach zawierających NX:
        T() -> update(L() -> T(), R() -> T(), 1, BaseY, NY);
    }

    //Zczytywanie gcd z prostokąta:
    ll read(int lo, int hi, int lX, int rX, int lY, int rY)
    {
        if (rX < lo || hi < lX) return 0;
        if (lX <= lo && hi <= rX)
        {
            return T() -> read(1, BaseY, lY, rY);
        }

        int mid = (lo + hi) >> 1;
        return __gcd(L() -> read(lo, mid, lX, rX, lY, rY),
                     R() -> read(mid + 1, hi, lX, rX, lY, rY));
    }
};

NodeX * Tree = new NodeX();

void update(int a, int b, ll v)
{
    Tree -> chTree(1, BaseX, a, b, v);
}

ll query(int a, int b, int c, int d)
{
    return Tree -> read(1, BaseX, a, c, b, d);
}
