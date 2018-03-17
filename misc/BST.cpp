//Niezrównoważone drzewo BST
//Złożoność operacji insert, read, erase:
//1) dla danych, w których każda wartość może wystąpić z równym prawdopodobieństwem: O(log N)
//2) pesymistyczna: O(N)

struct BST
{
    BST * left, * right;
    int v, sz;

    BST() : left(nullptr), right(nullptr), v(0), sz(0) {}

    BST * L()
    {
        if (left == nullptr) left = new BST();
        return left;
    }

    BST *R()
    {
        if (right == nullptr) right =  new BST();
        return right;
    }

    ~BST()
    {
        delete left;
        delete right;
    }

    //Wstawia wartość x do drzewa
    void insert(int x)
    {
        if (!sz)
        {
            sz = 1;
            v = x;
            return ;
        }
        if (x <= v) L() -> insert(x);
        else R() -> insert(x);
        sz = L() -> sz + R() -> sz + 1;
    }

    //Zczytuje wartość k - tego najmniejszego elementu drzewa
    int read(int k)
    {
        if (sz == 1) return v;
        if (L() -> sz >= k) return L() -> read(k);
        if (k - L() -> sz > 1) return R() -> read(k - L() -> sz - 1);
        return v;
    }

    //Niedziałające usuwanie wartości z drzewa
    /*BST * getMax(int x)
    {
        if (sz == 1) return this;
        if (L() -> v * x >= v * x) return L() -> getMax(x);
        return R() -> getMax(x);
    }

    void erase(int x)
    {
        if (v == x)
        {
            BST * cur = this;
            if (L() -> sz == 0) cur = cur -> right;
            else if (R() -> sz == 0) cur = cur -> left;
            else
            {
                BST * N = L() -> getMax(1);
                left = N -> left;
                v = N -> v;
                N -> erase(v);
            }
        }
        else
        {
            if (x <= v) L() -> erase(x);
            else R() -> erase(x);
        }
        sz = L() -> sz + R() -> sz + 1;
    }*/

    //Wypisuje zawartość drzewa posortowaną niemalejąco
    void sort()
    {
        if (!sz) return ;
        L() -> sort();
        cout << v << " ";
        R() -> sort();
    }
};
