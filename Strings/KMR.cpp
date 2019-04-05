#define st first
#define nd second

struct KMR {
    vector<pair<pair<int, int>, int>> x;
    vector<vector<int>> kmr;
    vector<int> s;
    int n;

    KMR(vector<int> s_) : s(s_) {
        n = s.size();
        x.resize(n);
        kmr.push_back(s);
        int k, p;
        for (k = 1, p = 1; 2 * p < n; k++, p *= 2) {
            kmr.push_back(vector<int>(n - 2 * p + 1));
            x.resize(n - 2 * p + 1);
            for (int i = 0; i + 2 * p <= n; i++) {
                x[i] = {{kmr[k - 1][i], kmr[k - 1][i + p]}, i};
            }

            sort(x.begin(), x.end());
            int id = 0;
            for (int i = 0; i < x.size(); i++) {
                if (i && x[i - 1].st != x[i].st) {
                    id++;
                }
                kmr[k][x[i].nd] = id;
            }
        }
    }

    pair<int, int> Hash(int a, int b) {
        if (a == b) {
            return {kmr[0][a], kmr[0][a]};
        }
        int p = 31 - __builtin_clz(b - a);
        return {kmr[p][a], kmr[p][b - (1 << p) + 1]};
    }
};
