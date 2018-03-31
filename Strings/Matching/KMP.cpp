// matchPattern returns list of occurrences of pattern p in string s
// You can also match a pattern by creating KMP for string: p + 'S' + s
// Complexity: O(|s| + |p|)
// Source: wazniak.mimuw.edu.pl
// Usage: [CF Round #246] Prefixes and Suffixes http://codeforces.com/problemset/problem/432/D

struct KMP
{
    int N;
    string p;
    vector<int> ps;

    KMP(string p) : N((int)p.size()), p(p), ps(N, 0)
    {
        int k = -1;
        for (int i = 0; i < N; i++)
        {
            while (p[k] != p[i] && k >= 0)
            {
                if (k == 0) k = -1;
                else k = ps[k - 1];
            }
            k++;
            ps[i] = k;
        }
    }

    vector<int> matchPattern(string s)
    {
        vector<int> occur;
        int k = 0;
        for (int i = 0; i < s.size();  i++)
        {
            while (p[k] != s[i] && k >= 0)
            {
                if (k == 0) k = -1;
                else k = ps[k - 1];
            }
            k++;
            if (k == N) occur.push_back(i - N + 1);
        }
        return occur;
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
            int sz = Size[P[i]-1];
            if (P[i] && i - sz <= Range[sz - 1])
            {
                Size[i] = sz;
                Range[sz - 1] = i;
            }
        }
    }
};
