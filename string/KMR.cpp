#define para pair<pair<int, int>,int>
#define st first
#define nd second

struct kmr
{
    //Tablica podsłów bazowych
    vector<vector<int>> KMR;
    //pp[i] = wykładnik przy największej potędze dwójki mniejszej od i
    vector<int> pp;
    //długość słowa, log2(N), rozmiar alfabetu
    int N, LOG, SIGMA;

    kmr(string &s) : N(s.size()), LOG(ceil(log2(s.size()))), SIGMA(255), pp(s.size()+3), KMR(ceil(log2(s.size())+1), vector<int>(s.size()+500, 0))
    {
        //Hasze dla fragmentów długości 1 to ich kod ASCII
        for (int i = 0; i < N; i++)
        {
            KMR[0][i] = (int)s[i];
        }

        //Obliczanie haszy dla fragmentów długości 2^(j+1) dla j < log2(N)
        for (int j = 0; j < LOG; j++)
        {
            static vector<para> bucket[2][MAXN];
            for (int i = 0; i < N; i++)
            {
                //Początkowo drugi element pary to 0, bo może on być z poza słowa
                para suf = {{KMR[j][i], 0}, i};
                //Jeżeli drugi element pary mieści się w słowie:
                if (i + (1 << j) < N)
                {
                    suf.st.nd = KMR[j][i + (1 << j)];
                }
                //Sortuj kubełkowo po drugim elemencie pary
                bucket[0][suf.st.nd].push_back(suf);
            }

            for (int k = 0; k <= SIGMA; k++)
            {
                for (auto i : bucket[0][k])
                {
                    //Sortuj kubełkowo po pierwszym elemencie pary
                    bucket[1][i.st.st].push_back(i);
                }
                bucket[0][k].clear();
                bucket[0][k].shrink_to_fit();
            }

            int hasz = 0;
            para prev = {{0, 0}, 0};

            for (int k = 0; k <= SIGMA; k++)
            {
                for (auto i : bucket[1][k])
                {
                    //Jeżeli obecna para i poprzednia są takie same, to mają takie same hasze
                    //W przeciwnym wypadku hasz obecnej pary jest większy o jeden
                    KMR[j + 1][i.nd] = hasz + (prev.st != i.st);
                    hasz = KMR[j + 1][i.nd];
                    prev = i;
                }
                bucket[1][k].clear();
                bucket[1][k].shrink_to_fit();
            }
            SIGMA = hasz;
        }

        for (int i = 1; i < LOG; i++)
        {
            for (int j = (1 << i) + 1; j <= (1 << (i + 1)) && j <= N; j++)
            {
                pp[j] = i;
            }
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
