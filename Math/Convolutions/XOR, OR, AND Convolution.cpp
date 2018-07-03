// xorConv = FWHT
// orConv = OR Convolution
// andConv = AND Convolution
// Matrices for transforms and their inverses:
// XOR:
// +1 +1   +1 +1
// +1 -1   +1 -1
// OR:
// +1 +1    0 +1
// +1  0   -1 +1
// AND:
//  0 +1   -1 +1
// +1 +1   +1  0
// Complexity: O(n * log n)

using ll = long long;

void transform(vector<int> &a, int bit, bool inv)
{
    for (int len = 1; 2 * len <= a.size(); len *= 2)
    {
        for (int i = 0; i < a.size(); i += 2 * len)
        {
            for (int j = 0; j < len; j++)
            {
                ll x = a[i + j], y = a[i + j + len];
                if (!inv)
                {
                    if (!bit) a[i + j] = x + y, a[i + j + len] = x - y;
                    else if (bit == 1) a[i + j] = x + y, a[i + j + len] = x;
                    else if (bit == 2) a[i + j] = y, a[i + j + len] = x + y;
                }
                else
                {
                    if (!bit) a[i + j] = x + y, a[i + j + len] = x - y;
                    else if (bit == 1) a[i + j] = y, a[i + j + len] = x - y;
                    else if (bit == 2) a[i + j] = -x + y, a[i + j + len] = x;
                }
            }
        }
    }
}

vector<int> conv(vector<int> a, vector<int> b, int bit)
{
    int sz = max(a.size(), b.size()), n = 1;
    if (sz <= 0) return {};
    while (n < sz) n <<= 1;

    a.resize(n); transform(a, bit, 0);
    b.resize(n); transform(b, bit, 0);

    for (int i = 0; i < n; i++) a[i] *= b[i];

    transform(a, bit, 1);

    return a;
}

vector<int> xorConv(vector<int> a, vector<int> b)
{
    a = conv(a, b, 0);
    for (auto &i : a) i /= a.size();
    return a;
}

vector<int> orConv(vector<int> a, vector<int> b)
{
    return conv(a, b, 1);
}

vector<int> andConv(vector<int> a, vector<int> b)
{
    return conv(a, b, 2);
}
