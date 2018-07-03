// FFT - Fast Fourier Transform
// Uses bit-reversal permutation to rearrange coefficients of the polynomial
// in order to allow easy and efficient iterative approach
// For the same reason preprocesses roots of unity and their powers.
// To deal with bigger numbers and/or longer polynomials change vector<int> to vector<ll>
// Complexity: O(n * log n)
// Source: wazniak.mimuw.edu.pl, e-maxx.ru, github.com/bqi343

using cd = complex<double>;
using ll = long long;

// Multiplies a and b using brute force
vector<int> brute(vector<int> &a, vector<int> &b)
{
    vector<int> ab(a.size() + b.size() - 1);
    for (int i = 0; i < a.size(); i++)
    {
        for (int j = 0; j < b.size(); j++)
        {
            ab[i + j] += a[i] * b[j];
        }
    }
    return ab;
}

// Preprocessing of bit-reversal permutation and roots of unity
void dftPreprocessing(vector<int> &rev, vector<vector<cd>> &root, int n)
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
    for (int len = 2, bit = 1; len <= n; len <<= 1, bit++)
    {
        root[bit].resize(len);
        cd wlen(cos(2 * M_PI / len), sin(2 * M_PI / len));
        root[bit][0] = 1;
        for (int i = 1; i < len; i++) root[bit][i] = root[bit][i - 1] * wlen;
    }
}

// DFT - Discrete Fourier Transform
void dft(vector<cd> &a, bool inv)
{
    int n = a.size();
    if (n == 1) return;

    static vector<int> rev;
    static vector<vector<cd>> root;
    if (rev.empty()) dftPreprocessing(rev, root, n);

    for (int i = 0; i < n; i++) if (i < rev[i]) swap(a[i], a[rev[i]]);

    for (int len = 1, bit = 1; 2 * len <= n; len <<= 1, bit++)
    {
        for (int i = 0; i < n; i += 2 * len)
        {
            for (int j = 0; j < len; j++)
            {
                cd x = a[i + j], y = root[bit][i] * a[i + j + len];
                a[i + j] = x + y;
                a[i + j + len] = x - y;
            }
        }
    }

    if (inv) reverse(a.begin() + 1, a.end());
}

// FFT convolution of a and b (multiplies a and b)
vector<int> fft(vector<int> a, vector<int> b)
{
    int sz = a.size() + b.size() - 1, n = 1;
    if (sz <= 250) return brute(a, b);
    while (n < sz) n <<= 1;

    vector<cd> A(a.begin(), a.end()), B(b.begin(), b.end());

    A.resize(n); dft(A, 0);
    B.resize(n); dft(B, 0);

    for (int i = 0; i < n; i++) A[i] *= B[i];

    dft(A, 1); a.resize(sz);
    for (int i = 0; i < sz; i++) a[i] = round(A[i].real() / n);

    return a;
}
