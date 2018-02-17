const int MAXN = 5e5 + 5;

struct Pair
{
    int h1, h2, pos;
    bool operator != (const Pair &b) const
    {
        return (h1 != b.h1 || h2 != b.h2);
    }
};

struct kmr
{
    //Tablica haszy dla posłów bazowych:
    vector<vector<int>> KMR;
    //Tablica do sortowania kubełkowego:
    vector<vector<vector<Pair>>> bucket;
    //pp[i] - wykładnik przy największej potędze dwójki mniejszej od lub równej i
    vector<int> pp;
    int n; // długość słowa

    kmr(string &s) : n(s.size()), pp(s.size() + 3), bucket(2, vector<vector<Pair>>(max((int)s.size(), 355)))
    {
        int ALPHA = 0; //Wartość największego hasza
        vector<Pair> pairs(n);
        //lex[i] - hasz podsłowa zaczynającego się w s[i]
        vector<int> lex(n);

        //Hasze dla podsłów długości 1 to ich numery ASCII
        for (int i = 0; i < n; i++)
        {
            lex[i] = (int)s[i];
            ALPHA = max(ALPHA, lex[i]);
        }

        KMR.push_back(lex);

        //Obliczanie haszy dla podsłów długości 2 ^ (p + 1):
        int p = 2;
        while (p < n)
        {
            lex.resize(n - p + 1);
            pairs.resize(n - p + 1);
            for (int i = 0; i <= n - p; i++)
            {
                pairs[i] = {lex[i], lex[i + p / 2], i};
            }

            //Sortowanie kubełkowe wszystkich par:
            bucket_sort(pairs, ALPHA);

            ALPHA = 0;

            //Zahaszowanie podsłów:
            lex[pairs[0].pos] = 0;
            for (int i = 1; i <= n - p; i++)
            {
                //Jeżeli dwa podsłówa są takie same to mają taki sam hasz
                if (pairs[i] != pairs[i - 1]) ALPHA++;
                lex[pairs[i].pos] = ALPHA;
            }
            KMR.push_back(lex);
            p *= 2;
        }

        p = 0;
        for (int i = 1; i <= n; i++)
        {
            if (__builtin_popcount(i) == 1) p++;
            pp[i] = p;
        }
    }

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

    pair<int, int> Hasz(int l, int r)
    {
        int p = pp[r - l + 1];
        return {KMR[p][l], KMR[p][r - (1 << p) + 1]};
    }

    bool cmpSubstr(int a, int b, int c, int d)
    {
        if (b - a != d - c) return 0;
        return Hasz(a, b) == Hasz(c, d);
    }
};
