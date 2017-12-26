//Hasze

using ll = long long;

struct Hasze
{
    vector<int> H, pp;
    int N, p, mod;

    Hasze(string s, int p, int mod) : N(s.size()), p(p), mod(mod), H(s.size()), pp(s.size())
    {
        pp[0] = 1;
        H[0] = s[0] - 'a' + 1;
        for (int i = 1; i < N; i++)
        {
            pp[i] = ((ll)pp[i-1] * (ll)p)%mod;
            H[i] = ((ll)H[i-1] * (ll)p + s[i] - 'a' + 1)%mod;
        }
    }

    int Hasz(int l, int r)
    {
        if (l == 0) return H[r];
        return ((H[r] - (ll)H[l-1] * (ll)pp[(r-l+1)])%mod + mod)%mod;
    }

    int Haszuj(string s)
    {
        int hasz = 0;
        for (int i = 0; i < s.size(); i++)
        {
            hasz = ((ll)hasz * (ll)p + s[i] - 'a' + 1)%mod;
        }
        return hasz;
    }

    bool cmpSubstrings(int a, int b, int c, int d)
    {
        return Hasz(a, b) == Hasz(c, d);
    }

    vector<int> matchPattern(string pat)
    {
        int hasz = Haszuj(pat), m = pat.size();
        vector<int> is;
        for (int i = 0; i + m - 1 < N; i++)
        {
            if (Hasz(i, i + m - 1) == hasz)
            {
                is.push_back(i);
            }
        }
        return is;
    }
};
