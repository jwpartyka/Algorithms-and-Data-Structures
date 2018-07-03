// Karatsuba polynomial multiplication
// Complexity: O(n ^ log 3) = O(n ^ 1.58), n = max(a.size() b.size())
// USAGE: [SPOJ] MUL http://www.spoj.com/problems/MUL/
//               POLYMUL http://www.spoj.com/problems/POLYMUL/

using ll = long long;

// Multiplies a and b using brute force
vector<ll> brute(vector<ll> &a, vector<ll> &b)
{
    vector<ll> ab(a.size() + b.size());
    for (int i = 0; i < a.size(); i++)
    {
        for (int j = 0; j < b.size(); j++)
        {
            ab[i + j] += a[i] * b[j];
        }
    }
    return ab;
}

vector<ll> karatsuba(vector<ll> a, vector<ll> b)
{
    int sz = a.size() + b.size(), n = 1;
    if (sz <= 64) return brute(a, b);
    while (2 * n < sz) n <<= 1;

    a.resize(n), b.resize(n);

    vector<ll> A = karatsuba(vector<ll>(a.begin(), a.begin() + n / 2),
                                vector<ll>(b.begin(), b.begin() + n / 2));
    vector<ll> B = karatsuba(vector<ll>(a.begin() + n / 2, a.end()),
                                vector<ll>(b.begin() + n / 2, b.end()));

    for (int i = 0; i < n / 2; i++)
    {
        a[i] += a[i + n / 2];
        b[i] += b[i + n / 2];
    }

    vector<ll> C = karatsuba(vector<ll>(a.begin(), a.begin() + n / 2),
                                vector<ll>(b.begin(), b.begin() + n / 2));

    a.resize(sz);
    fill(a.begin(), a.end(), 0);
    for (int i = 0; i < n; i++)
    {
        a[i] += A[i];
        a[i + n / 2] += (C[i] - A[i] - B[i]);
        a[i + n] += B[i];
    }
    a.pop_back();
    return a;
}

// Multiplies polynomials a and b
vector<ll> mul(vector<ll> a, vector<ll> b)
{
    int sz = a.size() + b.size() - 1, n = 1;
    while (n < max(a.size(), b.size())) n <<= 1;
    a.resize(n), b.resize(n);
    auto ab = karatsuba(a, b);
    return vector<ll>(ab.begin(), ab.begin() + sz);
}
