// FFT
// Complexity: O(n * logn)
// Source: wazniak.mimuw.edu.pl, e-maxx.ru, Benjamin Qi

using cd = complex<double>;

// Multiplies a and b using brute force
vector<cd> brute(vector<cd> &a,  vector<cd> &b)
{
    vector<cd> ab(a.size() + b.size() - 1);
    for (int i = 0; i < a.size(); i++)
    {
        for (int j = 0; j < b.size(); j++)
        {
            ab[i + j] += a[i] * b[j];
        }
    }
    return ab;
}

// DFT - Discrete Fourier Transform
void dft(vector<cd> &a, int inv)
{
    int n = a.size();
    if (n == 1) return;

    for (int i = 1, j = 0; i < n; i++)
    {
        int bit = n >> 1;
        while (j & bit)
        {
            j ^= bit;
            bit >>= 1;
        }
        j ^= bit;

        if (i < j) swap(a[i], a[j]);
    }

    for (int len = 2; len <= n; len <<= 1)
    {
        double ang = 2 * M_PI / len * inv;
        cd wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len)
        {
            cd w(1);
            for (int j = 0; j < len / 2; j++)
            {
                cd u = a[i + j], v = a[i + j + len / 2];
                a[i + j] = u + w * v;
                a[i + j + len / 2] = u - w * v;
                w *= wlen;
            }
        }
    }
}

// Inverse DFT
void idft(vector<cd> &a)
{
    dft(a, -1);
    for (auto &i : a) i /= a.size();
}

// FFT
vector<cd> fft(vector<cd> &a, vector<cd> &b)
{
    int sz = a.size() + b.size() - 1, n = 1;
    if (sz <= 250) return brute(a, b);
    while (n < sz) n <<= 1;

    a.resize(n);
    dft(a, 1);
    b.resize(n);
    dft(b, 1);

    for (int i = 0; i < n; i++) a[i] *= b[i];

    idft(a);
    a.resize(sz);

    return a;
}

// Multiplies a and b
vector<int> mul(vector<int> &a, vector<int> &b)
{
    vector<cd> A(a.begin(), a.end()), B(b.begin(), b.end());
    auto AB = fft(A, B);
    vector<int> ab;
    for (auto i : AB) ab.push_back(round(i.real()));
    return ab;
}
