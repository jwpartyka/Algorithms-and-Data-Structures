// Computing suffix array, LCP array and number of distinct substrings of string s.
// Suffix array is constructed using KMR.
// LCP is computed using Kasai's algorithm.
// Complexity:
// - Suffix array: O(|s| * log^2 |s|)
// - LCP: O(|s|)
// - Number of distinct substrings: O(|s|)
// Source: Warsaw Eagles
// Usage: [SPOJ] SUBST1 http://www.spoj.com/problems/SUBST1/

using ll = long long;

#define st first
#define nd second

struct SA {
    vector<pair<pair<int, int>, int>> x;
    vector<int> sa;
    vector<int> rank;
    vector<int> lcp;
    vector<int> s;
    int n;

    SA(vector<int> s_) : s(s_) {
        n = s.size();
        x.resize(n);
        rank = s;
        for (int p = 1; p < n; p *= 2) {
            for (int i = 0; i < n; i++) {
                x[i] = {{rank[i], -1}, i};
                if (i + p < n) {
                    x[i].st.nd = rank[i + p];
                }
            }

            sort(x.begin(), x.end());
            int id = 0;
            for (int i = 0; i < n; i++) {
                if (i && x[i - 1].st != x[i].st) {
                    id++;
                }
                rank[x[i].nd] = id;
            }
        }

        sa.resize(n);
        for (int i = 0; i < n; i++) {
            sa[rank[i]] = i;
        }

        lcp.resize(n);
        int len = 0;
        for (int i = 0; i < n; i++) {
            len = max(0, len - 1);
            if (rank[i]) {
                while (s[sa[rank[i]] + len] == s[sa[rank[i] - 1] + len]) {
                    len++;
                }
            }
            lcp[rank[i]] = len;
        }
    }

    ll countDistinctSubstr() {
        ll res = 0;
        for (int i = 0; i < n; i++) {
            res += n - sa[i] - lcp[i];
        }
        return res;
    }
};
