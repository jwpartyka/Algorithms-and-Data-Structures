// Returns Z - Array of string S
// To search for pattern P in string T: S = P + '$' + T
// Complexity: O(|S|)
// Usage: [CF Round #246] Prefixes and Suffixes http://codeforces.com/problemset/problem/432/D

vector<int> Z_Function(string s)
{
    vector<int> Z(s.size());
    int i = 1, m = 1, len = 0, n = s.size();
    while (i < n)
    {
        m = i;

        // While string s[i...i + len] doesn't reach over the end of string s
        // and is equal to the preffix s[0...len]
        while (i + len < n && s[i + len] == s[len])
        {
            len++;
        }
        Z[i] = len;
        i++;
        // While it's possible to compute Z[i] using values computed beforehand
        while (i + Z[i - m] < m + len)
        {
            Z[i] = Z[i - m];
            i++;
        }

        // Updates the length of the current longest matching preffix
        // If (i - m > len) -> len = 0, else -> len -= (i - m)
        len -= min(len, i - m);
    }
    return Z;
}
