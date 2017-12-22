//Drzewo przedziałowe przedział-przedział (+, suma) ze skalowaniem
//Końce przedziałów z zapytań po przeskalowaniu będą zajmować kolejne
//liście o parzystych numerach. Liść o numerze 2*k+1 to składowa punktów
//z przedziału pomiędzy liściami 2*k i 2*k+2. Nigdy nie zapytamy o przedział
//o końcu w liściu nieparzystym, ale liście te pomagają utrzymywać odpowiednie
//rozmiary przedziałów i wyniki.

#define st first
#define nd second
#define mid (left+right)/2 //środek przedziału w drzewie przedziałowym

const int MAXN = 5e5+5;
struct Node
{
    int res, lazy, sz, og;
};

Node Tree[2*1024*1024];
int zap[MAXN][4], Base = 1;
map<int, int> sc;

//Obliczenie rzeczywistych rozmiarów przedziałów
void calcSizes(int node)
{
    if (node >= Base) return ;
    calcSizes(2*node), calcSizes(2*node+1);
    Tree[node].sz = Tree[2*node].sz + Tree[2*node+1].sz;
}

void zepchnij(int node)
{
    for (int i = 2*node; i <= 2*node+1; i++)
    {
        Tree[i].res += Tree[i].sz * Tree[node].lazy;
        Tree[i].lazy += Tree[node].lazy;
    }
    Tree[node].lazy = 0;
}

void chTree(int node, int left, int right, int l, int r, int v)
{
    if (r < left || right < l) return ;
    if (l <= left && right <= r)
    {
        Tree[node].res += Tree[node].sz * v;
        Tree[node].lazy += v;
        return ;
    }
    zepchnij(node);
    chTree(2*node, left, mid, l, r, v);
    chTree(2*node+1, mid+1, right, l, r, v);
    Tree[node].res = Tree[2*node].res + Tree[2*node+1].res;
}

int read(int node, int left, int right, int l, int r)
{
    if (r < left || right < l) return 0;
    if (l <= left && right <= r)
    {
        return Tree[node].res;
    }
    zepchnij(node);
    return read(2*node, left, mid, l, r) + read(2*node+1, mid+1, right, l, r);
}

//Przeskalowanie i utworzenie nieparzystych liści
void scale()
{
    while (Base < 2 * sc.size() - 1) Base *= 2;
    int nr = 0;
    for (auto &v : sc)
    {
        Tree[nr+Base].og = v.st;
        Tree[nr+Base].sz = 1;
        v.nd = nr;
        nr += 2;
    }
    for (int i = 1; i < nr-2; i += 2)
    {
        Tree[i+Base].og = Tree[Base+i+1].og - 1;
        Tree[i+Base].sz = Tree[i+Base].og - Tree[i+Base-1].og;
    }
    calcSizes(1);
}

//Przykład zastosowania:
//Wczytanie zapytań, przeskalowanie, przetworzenie zapytań
int main()
{
    int q;
    cin >> q;
    for (int i = 0; i < q; i++)
    {
        cin >> zap[i][0];
        if (zap[i][0] == 1)
        {
            for (int j = 1; j <= 2; j++)
            {
                cin >> zap[i][j];
                sc[zap[i][j]];
            }
            cin >> zap[i][3];
        }
        else
        {
            for (int j = 1; j <= 2; j++)
            {
                cin >> zap[i][j];
                sc[zap[i][j]];
            }
        }
    }

    scale();

    for (int i = 0; i < q; i++)
    {
        if(zap[i][0] == 1)
        {
            chTree(1, 0, Base-1, sc[zap[i][1]], sc[zap[i][2]], zap[i][3]);
        }
        else cout << read(1, 0, Base-1, sc[zap[i][1]], sc[zap[i][2]]) << "\n";
    }
}
