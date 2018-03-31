// Computing suffix array, LCP array and number of distinct substrings of string s
// Suffix array is constructed using KMR with bucket sort
// LCP is computed using Kasai's algorithm
// Complexity:
// Suffix array: O(|s| * log |s|)
// LCP: O(|s|)
// Number of distinct substrings: O(|s|)
// Usage: [SPOJ] SUBST1 http://www.spoj.com/problems/SUBST1/

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

// lex[i] - hash of the substring beginning in s[i]
int lex[MAXN];
vector<Pair> bucket[2][MAXN]; // Array for bucket sort

void bucket_sort(vector<Pair> &pairs, int ALPHA)
{
    // Sorts by the second element of pair
    for (auto p : pairs)
    {
        bucket[0][p.h2].push_back(p);
    }

    // Sorts by the first element of pair
    for (int i = 0; i <= ALPHA; i++)
    {
        for (auto p : bucket[0][i])
        {
            bucket[1][p.h1].push_back(p);
        }
        bucket[0][i].clear();
    }

    // Fills the vector with sorted pairs
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
    int ALPHA = 1; // Value of the largest hash
    vector<Pair> pairs(n);

    // Hashes of substring of length 1 are their ASCII numbers + 1
    for (int i = 0; i < n; i++)
    {
        lex[i] = ((int)s[i] + 1);
        ALPHA = max(ALPHA, lex[i]);
    }

    // Computes hashes for substrings of length 2 ^ (p + 1)
    for (int p = 0; (1 << p) < n; p++)
    {
        for (int i = 0; i < n; i++)
        {
            Pair P = {lex[i], 0, i};
            if (i + (1 << p) < n)
            {
                P.h2 = lex[i + (1 << p)];
            }
            pairs[i] = P;
        }

        // Bucket sort of all pairs
        bucket_sort(pairs, ALPHA);

        ALPHA = 1;

        // Compresses hashes
        lex[pairs.front().pos] = 1;
        for (int i = 1; i < n; i++)
        {
            // If two substrings are the same they have the same hash
            if (pairs[i] != pairs[i - 1]) ALPHA++;
            lex[pairs[i].pos] = ALPHA;
        }
    }

    // Fills the suffix array
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
        // Compares suffixes letter by letter
        while (s[i + len] == s[ SA[lex[i]] + len])
        {
            len++;
        }
        LCP[lex[i] - 1] = len;
    }
    return LCP;
}

ll countDistinctSubstr(vector<int> &SA, vector<int> &LCP)
{
    int n = SA.size();
    ll res = (ll)n * n;
    for (int i : SA) res -= i;
    for (int i : LCP) res -= i;
    return res;
}
