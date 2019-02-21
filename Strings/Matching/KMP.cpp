// Complexity: O(|s|)
// Usage: [CF Round #246] Prefixes and Suffixes http://codeforces.com/problemset/problem/432/D

vector<int> KMP(string s) {
    int n = s.size();
    vector<int> ps(n);

    int len = -1;
    for (int i = 0; i < n; i++) {
        while (len >= 0 && s[len] != s[i]) {
            if (len == 0) {
                len = -1;
            } else {
                len = ps[len - 1];
            }
        }

        ps[i] = ++len;
    }

    return ps;
}
