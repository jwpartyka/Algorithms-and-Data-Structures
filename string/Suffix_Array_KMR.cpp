//Obliczanie tablicy sufiksowej, tablicy LCP oraz liczby róznych podsłów dla słowa s
//Tablice sufiksową oblicza się poprzez KMR w O(|s| * log|s|)
//LCP oblicza się algorytmem Kasai w O(|s|)
//Liczba różnych podsłów w O(|s|)

using ll = long long;

const int MAXN = 5e5 + 5;

struct Pair
{
    int h1, h2, pos;
    bool operator != (const Pair &b) const
    {
        return (h1 != b.h1 || h2 != b.h2);
    }
};

//lex[i] - hasz podsłowa zaczynającego się w s[i]
int lex[MAXN];
vector<Pair> bucket[2][MAXN]; //Tablica do sortowania kubełkowego:

void bucket_sort(vector<Pair> &pairs, int ALPHA)
{
    //Sortowanie po drugim elemencie pary
    for (auto p : pairs)
    {
        bucket[0][p.h2].push_back(p);
    }

    //Sortowanie po pierwszym elemencie pary
    for (int i = 0; i <= ALPHA; i++)
    {
        for (auto p : bucket[0][i])
        {
            bucket[1][p.h1].push_back(p);
        }
        bucket[0][i].clear();
    }

    //Uzupełnianie wektora parami w posortowanej kolejności
    int ind = 0;
    for (int i = 0; i <= ALPHA; i++)
    {
        for (auto p : bucket[1][i])
        {
            pairs[ind++] = p;
        }
        bucket[1][i].clear();
    }
}

vector<int> saBuild(string &s)
{
    int n = s.size();
    int ALPHA = 1; //Wartość największego hasza
    vector<Pair> pairs(n);

    //Hasze dla podsłów długości 1 to ich numery ASCII + 1
    for (int i = 0; i < n; i++)
    {
        lex[i] = ((int)s[i] + 1);
        ALPHA = max(ALPHA, lex[i]);
    }

    //Obliczanie haszy dla podsłów długości 2 ^ (p + 1):
    int p = 2;
    while (p < n)
    {
        for (int i = 0; i < n; i++)
        {
            Pair P = {lex[i], 0, i};
            if (i + p / 2 < n)
            {
                P.h2 = lex[i + p / 2];
            }
            pairs[i] = P;
        }

        //Sortowanie kubełkowe wszystkich par:
        bucket_sort(pairs, ALPHA);

        ALPHA = 1;

        //Zahaszowanie podsłów:
        lex[pairs[0].pos] = 1;
        for (int i = 1; i < n; i++)
        {
            //Jeżeli dwa podsłówa są takie same to mają taki sam hasz
            if (pairs[i] != pairs[i - 1]) ALPHA++;
            lex[pairs[i].pos] = ALPHA;
        }
        p *= 2;
    }

    //Uzupełnia tablicę sufiksową:
    vector<int> SA(n);
    for (int i = 0; i < n; i++)
    {
        SA[lex[i] - 1] = i;
    }
    return SA;
}

vector<int> lcpBuild(string &s, vector<int> &SA)
{
    int n = s.size();
    vector<int> LCP(n, 0);

    int len = 0;
    for (int i = 0; i < n; i++)
    {
        //LCP[i + 1] >= LCP[i] - 1
        len = max(0, len - 1);
        if (lex[i] == n) continue;
        //Porównywanie kolejnych sufiksów literka po literce:
        while (s[i + len] == s[ SA[lex[i]] + len])
        {
            len++;
        }
        LCP[lex[i] - 1] = len;
    }
    return LCP;
}

ll liczbaRoznychPodslow(vector<int> &SA, vector<int> &LCP)
{
    int n = SA.size();
    ll res = (ll)n * n;
    for (int i : SA) res -= i;
    for (int i : LCP) res -= i;
    return res;
}
