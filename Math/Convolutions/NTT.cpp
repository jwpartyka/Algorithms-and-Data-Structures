// NTT - Number Theoretic Transform
// Uses bit-reversal permutation to rearrange coefficients of the polynomial
// in order to allow easy and efficient iterative approach
// For the same reason preprocesses roots of unity and their powers.
// Complexity: O(n * log n)
// Source: wazniak.mimuw.edu.pl, e-maxx.ru, github.com/bqi343

using ll = long long;

const int mod = (119 << 23) + 1, gen = 3;
//const int mod = (107 << 23) + 1, gen = 3;
//const int mod = (479 << 21) + 1, gen = 3;
//const int mod = (483 << 21) + 3, gen = 5;

// a^b modulo mod
int modPow(int a, int b, int mod)
{
    if (b <= 0) return 1;
    if (b & 1) return ((ll) a * modPow(a, b - 1, mod)) % mod;
    int c = modPow(a, b / 2, mod);
    return ((ll) c * c) % mod;
}

// Modular inverse of a modulo mod
int modInv(int a, int mod)
{
    return modPow(a, mod - 2, mod);
}

// Multiplies a and b using brute force
vector<int> brute(vector<int> &a, vector<int> &b)
{
    vector<int> ab(a.size() + b.size() - 1);
    for (int i = 0; i < a.size(); i++)
    {
        for (int j = 0; j < b.size(); j++)
        {
            ab[i + j] = ((ll) ab[i + j] + (ll) a[i] * b[j]) % mod;
        }
    }
    return ab;
}

// Preprocessing of bit-reversal permutation and roots of unity
void dftPreprocessing(vector<int> &rev, vector<vector<int>> &root, int n)
{
    rev.resize(n);
    for (int i = 1, j = 0; i < n; i++)
    {
        int bit = n >> 1;
        while (j & bit)
        {
            j ^= bit;
            bit >>= 1;
        }
        j ^= bit;
        rev[i] = j;
    }

    root.resize(25);
    int qn = modPow(gen, (mod - 1) / n, mod);
    for (int len = 2, bit = 1; len <= n; len <<= 1, bit++)
    {
        root[bit].resize(len);
        int qlen = modPow(qn, n / len, mod);
        root[bit][0] = 1;
        for (int i = 1; i < len; i++) root[bit][i] = ((ll) root[bit][i - 1] * qlen) % mod;
    }
}

// DFT - Discrete Fourier Transform
void dft(vector<int> &a, bool inv)
{
    int n = a.size();
    if (n == 1) return;

    static vector<int> rev;
    static vector<vector<int>> root;
    if (rev.empty()) dftPreprocessing(rev, root, n);

    for (int i = 0; i < n; i++) if (i < rev[i]) swap(a[i], a[rev[i]]);

    for (int len = 1, bit = 1; 2 * len <= n; len <<= 1, bit++)
    {
        for (int i = 0; i < n; i += 2 * len)
        {
            for (int j = 0; j < len; j++)
            {
                int x = a[i + j], y = ((ll) root[bit][j] * a[i + j + len]) % mod;
                a[i + j] = x + y - (x + y >= mod ? mod : 0);
                a[i + j + len] = x - y + (x - y < 0 ? mod : 0);
            }
        }
    }

    if (inv) reverse(a.begin() + 1, a.end());
}

// NTT convolution of a and b (multiplies a and b modulo mod)
vector<int> ntt(vector<int> a, vector<int> b)
{
    int sz = a.size() + b.size() - 1, n = 1;
    if (sz <= 2) return brute(a, b);
    while (n < sz) n <<= 1;

    a.resize(n); dft(a, 0);
    b.resize(n); dft(b, 0);

    for (int i = 0; i < n; i++) a[i] = ((ll) a[i] * b[i]) % mod;

    dft(a, 1); a.resize(sz);
    int n_inv = modInv(n, mod);
    for (auto &i : a) i = ((ll) i * n_inv) % mod;

    return a;
}
