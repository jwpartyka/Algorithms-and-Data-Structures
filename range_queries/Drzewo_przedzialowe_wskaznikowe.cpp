//Dynamicczne drzewo przedział-przedział (+, suma);
//Korzeń drzewa obejmuje wartości [0...zakres_wartosci]
//Można używać zamiast skalowania
//Złożoność zapytania: O(log(Base))

#define mid (left+right)/2 //środek przedziału w drzewie przedziałowym

int Base = 1024*1024*1024;
//Base = najmniejsza potęga dwójki >= maksymalnej długości przedziału

struct Node
{
    Node * l,  * r;
    int sum, lazy, sz;

    //Konstruktor inicjalizujący wartości w węźle
    Node(int Size) : l(nullptr), r(nullptr), sum(0), lazy(0), sz(Size) {}

    //Destruktor
    ~Node()
    {
        delete l;
        delete r;
    }

    //Tworzy lewego syna jeżeli nie istnieje
    Node* L()
    {
        if (l == nullptr) l = new Node(sz/2);
        return l;
    }

    //Tworzy prawego syna jeżeli nie istnieje
    Node* R()
    {
        if (r == nullptr) r = new Node(sz/2);
        return r;
    }

    //Spychanie gwiazdki
    void zepchnij()
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
        zepchnij();
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
        zepchnij();
        return L()->read(left, mid, l, r) + R()->read(mid + 1, right, l, r);
    }
};

//Korzeń drzewa
Node * Tree = new Node(Base);
void Query(int l, int r, int v)
{
    if (v) Tree->chTree(0, Base-1, l, r, v);
    else cout << Tree->read(0, Base-1, l, r) << "\n";
}
