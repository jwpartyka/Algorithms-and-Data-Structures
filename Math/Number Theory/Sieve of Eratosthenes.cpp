// Sieve of Eratosthenes
// Complexity: O(N * log(log N))
// Prime factorization of n in O(log n)

const int MAXN = 1e6+5;

int sieve[MAXN], sum[MAXN];

// Computing the sieve
void calcSieve(int n)
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
    return sum[r] - sum[l - 1];
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
