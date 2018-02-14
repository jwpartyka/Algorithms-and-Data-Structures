//Obliczanie tablicy sufiksowej, tablicy LCP oraz liczby róznych podsłów dla słowa s
//Tablice sufiksową oblicza się poprzez KMR w O(|s| * log|s|)
//LCP oblicza się algorytmem Kasai w O(|s|)
//Liczba różnych podsłów w O(|s|)

#define st first
#define nd second
#define str pair<pair<int, int>, int>

using ll = long long;

const int MAXN = 2e5 + 5;

//lex[i] - które w kolejności leksykograficznej jest podsłowo bazowe zaczynające się na pozycji i
//id[i] - pozycja sufiksu zaczynającego się w i - tej literze w tablicy sufiksowej
//ALPHA - aktualna długość alfabetu (różnych podsłów bazowych)
int lex[MAXN], id[MAXN], ALPHA = 300;
//tablica kubełkowa do sortowania par:
vector<str> bucket[MAXN][2];

vector<int> saBuild(string s)
{
    ALPHA = 300;
    int n = s.size();
    vector<int> SA(n, 0);

    //Tablica lex dla podsłów długości 1 to ich numery ASCII
    for (int i = 0; i < n; i++)
    {
        lex[i] = ((int)s[i] + 1);
    }

    //Liczy tablicę lex dla kolejnych potęŋ dwójki:
    for (int p = 0; (1 << (p - 1)) <= n; p++)
    {
        for (int i = 0; i < n; i++)
        {
            //"Haszuje" podsłowa długości (2 ^ p):
            str suf = {{lex[i], 0}, i};
            if (i + (1 << p) < n) suf.st.nd = lex[i + (1 << p)];
            //Sortuje kubełkowo po drugim elemencie pary:
            bucket[suf.st.nd][0].push_back(suf);
        }

        //Sortuje kubełkowo po pierwszym elemencie pary:
        for (int i = 0; i < ALPHA; i++)
        {
            for (auto j : bucket[i][0])
            {
                 bucket[j.st.st][1].push_back(j);
            }
            bucket[i][0].clear();
        }

        //Przepisuje posortowane pary do wektora V:
        vector<str> V;
        for (int i = 0; i < ALPHA; i++)
        {
            for (auto j : bucket[i][1])
            {
                 V.push_back(j);
            }
            bucket[i][1].clear();
        }

        ALPHA = 300;
        if (V.empty()) continue;

        //Przeskalowuje wszystkie pary:
        lex[V[0].nd] = 1;
        for (int i = 1; i < V.size(); i++)
        {
            lex[V[i].nd] = lex[V[i - 1].nd] + (V[i].st != V[i - 1].st);
            ALPHA = max(ALPHA, lex[V[i].nd]);
        }
        ALPHA += 3;
    }

    //Uzupełnia tablicę sufiksową:
    for (int i = 0; i < n; i++)
    {
        SA[lex[i] - 1] = i;
        id[i] = lex[i] - 1;
    }
    return SA;
}

vector<int> lcpBuild(string s, vector<int> &SA)
{
    int n = s.size();
    s += '$';
    vector<int> LCP(n, 0);

    //Znajduje wynik brutalnie dla pierwszego sufiksu:
    if (id[0] < n - 1)
    {
        for (int i = 0; s[ SA[id[0] + 1] + i ] == s[i]; i++)
        {
            LCP[id[0]]++;
        }
    }

    //Uzupełnia tablicę LCP:
    for (int i = 1; i < n; i++)
    {
        if (id[i] == n - 1) continue;
        LCP[id[i]] = max(0, LCP[id[i - 1]] - 1);
        for (int j = max(0, LCP[id[i - 1]] - 1); s[ SA[id[i]] + j ] == s[ SA[id[i] + 1] + j]; j++)
        {
            LCP[id[i]]++;
        }
    }
    return LCP;
}

int liczbaRoznychPodslow(vector<int> &SA, vector<int> &LCP)
{
    int n = SA.size();
    ll res = (ll)n * (ll)n;
    for (int i : SA) res -= i;
    for (int i : LCP) res -= i;
    return res;
}
