//matchPattern zwraca wszystkie pozycje wystąpienia wzorca w tekście
//minCover zwraca długość najkrótszego słowa pokrywającego (szablonu)

struct KMP
{
    int N;
    string pat;
    vector<int> PS;
    KMP(string pat) : N((int)pat.size()), pat(pat), PS(N, 0)
    {
        int len = -1;
        for (int i = 0; i < N; i++)
        {
            while (len >= 0 && pat[len] != pat[i])
            {
                len = (len ? PS[len - 1] : -1);
            }
            PS[i] = ++len;
        }
    }

    vector<int> matchPattern(string t)
    {
        vector<int> is;
        int len = 0;
        for (int i = 0; i < t.size();  i++)
        {
            while (len >= 0 && pat[len] != t[i])
            {
                len = (len ? PS[len - 1] : -1);
            }
            len++;
            if (len == N) is.push_back(i - N + 1);
        }
        return is;
    }

    int minCover()
    {
        vector<int> Range, Size;
        for (int i = 0; i < N; i++)
        {
            Range.push_back(i);
            Size.push_back(i + 1);
        }

        for (int i = 0; i < N; i++)
        {
            int sz = Size[PS[i] - 1];
            if (PS[i] && i - sz <= Range[sz - 1])
            {
                Size[i] = sz;
                Range[sz - 1] = i;
            }
        }
        return Size.back();
    }
};
