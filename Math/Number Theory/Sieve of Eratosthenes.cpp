// Sieve of Eratosthenes
// Complexity:
// 1) Sieve: O(n * log log n)
// 2) Prime factorization: O(log n)

const int MAXN = 1e7+5;

int sieve[MAXN], sum[MAXN];

// Computing the sieve
void Sieve(int n)
{
    for (int i = 2; i * i <= n; i++)
    {
        if (!sieve[i])
        {
            for (int j = i * i; j <= n; j += i)
            {
                if (!sieve[j]) sieve[j] = i;
            }
        }
    }

    for (int i = 2; i <= n; i++)
    {
        sum[i] = sum[i - 1];
        if (!sieve[i])
        {
            sum[i]++;
            sieve[i] = i;
        }
    }
}

// Number of prime numbers in range [l, r]
int countPrimes(int l, int r)
{
    if (l) return sum[r] - sum[l - 1];
    return sum[r];
}

// Returns a vector with prime factorization of x
vector<int> factor(int x)
{
    vector<int> factors;
    while (sieve[x])
    {
        factors.push_back(sieve[x]);
        x /= sieve[x];
    }
    return factors;
}
