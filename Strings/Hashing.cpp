//Hashing

using ll = long long;

struct Hashe
{
    vector<int> H, pp;
    int N, p, mod;

    Hash(string s, int p, int mod) : N(s.size()), p(p), mod(mod), H(s.size()), pp(s.size())
    {
        pp[0] = 1;
        H[0] = s[0] - 'a' + 1;
        for (int i = 1; i < N; i++)
        {
            pp[i] = ((ll)pp[i-1] * (ll)p)%mod;
            H[i] = ((ll)H[i-1] * (ll)p + s[i] - 'a' + 1)%mod;
        }
    }

    int getHash(int l, int r)
    {
        if (l == 0) return H[r];
        return ((H[r] - (ll)H[l-1] * (ll)pp[(r-l+1)])%mod + mod)%mod;
    }

    int Hash(string s)
    {
        int hash = 0;
        for (int i = 0; i < s.size(); i++)
        {
            hash = ((ll)hash * (ll)p + s[i] - 'a' + 1)%mod;
        }
        return hash;
    }

    bool cmpSubstrings(int a, int b, int c, int d)
    {
        return getHash(a, b) == getHash(c, d);
    }

    vector<int> matchPattern(string pat)
    {
        int hash = Hash(pat), m = pat.size();
        vector<int> is;
        for (int i = 0; i + m - 1 < N; i++)
        {
            if (Hash(i, i + m - 1) == hash)
            {
                is.push_back(i);
            }
        }
        return is;
    }
};
