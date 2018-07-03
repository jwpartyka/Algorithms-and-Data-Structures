// AND Convolution
// Matrix for the transform and its inverse
//  0 +1   -1 +1
// +1 +1   +1  0
// -----------------------------------------------
// a | b = ~((~a) & (~b))
// swap(a[i], a[~i]) for 0 <= i < n / 2 reverses a
// Complexity: O(n * log n)

using ll = long long;

void transform(vector<int> &a, bool inv)
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
                    a[i + j] = y;
                    a[i + j + len] = x + y;
                }
                else
                {
                    a[i + j] = -x + y;
                    a[i + j + len] = x;
                }
            }
        }
    }
}

vector<int> andConv(vector<int> a, vector<int> b)
{
    int sz = max(a.size(), b.size()), n = 1;
    if (sz <= 0) return {};
    while (n < sz) n <<= 1;

    a.resize(n); transform(a, 0);
    b.resize(n); transform(b, 0);

    for (int i = 0; i < n; i++) a[i] *= b[i];

    transform(a, 1);

    return a;
}

vector<int> orConv(vector<int> a, vector<int> b)
{
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());

    a = andConv(a, b);

    reverse(a.begin(), a.end());

    return a;
}
