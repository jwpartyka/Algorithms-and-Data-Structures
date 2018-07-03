// FWHT - Fast Walsh-Hadamard Transform
// Matrix for the transform:
// +1 +1   +1 +1
// +1 -1   +1 -1
// Complexity: O(n * log n)

using ll = long long;

void fwht(vector<int> &a)
{
    for (int len = 1; 2 * len <= a.size(); len <<= 2)
    {
        for (int i = 0; i < a.size(); i += 2 * len)
        {
            for (int j = 0; j < len; j++)
            {
                int x = a[i + j], y = a[i + j + len];
                a[i + j] = x + y;
                a[i + j + len] = x - y;
            }
        }
    }
}

vector<ll> xorConv(vector<ll> a, vector<ll> b)
{
    int sz = max(a.size(), b.size()), n = 1;
    if (sz <= 0) return {};
    while (n < sz) n <<= 1;

    a.resize(n); fwht(a);
    b.resize(n); fwht(b);

    for (int i = 0; i < n; i++) a[i] *= b[i];

    fwht(a);
    for (auto &i : a) i /= n;

    return a;
}
