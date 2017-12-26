//matchPattern zwraca wszystkie pozycje wystąpienia wzorca w tekście

struct KMP
{
    int N;
    string pat;
    vector<int> ps;
    KMP(string pat) : N((int)pat.size()), pat(pat), ps(N, 0)
    {
        int k = -1;
        for (int i = 0; i < N; i++)
        {
            while (pat[k] != pat[i] && k >= 0)
            {
                if (k == 0) k = -1;
                else k = ps[k-1];
            }
            k++;
            ps[i] = k;
        }
    }

    vector<int> matchPattern(string t)
    {
        vector<int> is;
        int k = 0;
        for (int i = 0; i < t.size();  i++)
        {
            while (pat[k] != t[i] && k >= 0)
            {
                if (k == 0) k = -1;
                else k = ps[k-1];
            }
            k++;
            if (k == N) is.push_back(i-N+1);
        }
        return is;
    }
};
