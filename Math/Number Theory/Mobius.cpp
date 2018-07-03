// Mobius Function
// mu[1] = 1
// mu[n] = 0 if n has a squared prime factor
// mu[n] = 1 if n is a square - free positive integer with an even number of distinct prime factors
// mu[n] = -1 if n is a square - free positive integer with an odd number of distinct prime factors
// If n = p1 * p2 * ... * pk then n / -p1 / -p2 / ... / -pk = (-1)^k
// Sum of mu[d] for every divisor d of n equals 0
// If gcd(a, b) = 1 then mu[a * b] = mu[a] * mu[b]
// Complexity: O(n * log n)
// Source: Wikipedia
// Usage: Inclusion - Exclusion Principle

const int MAXN = 1e7+5;

int mu[MAXN], sieve[MAXN];

void Mobius(int n)
{
    for (int i = 1; i <= n; i++)
    {
        mu[i] = i;
    }

    for (int i = 2; i <= n; i++)
    {
        if (mu[i] == i)
        {
            for (int j = i; j <= n; j += i)
            {
                mu[j] /= -i;
            }
        }
    }

    for (int i = 1; i <= n; i++)
    {
        if (abs(mu[i]) == 1)
        {
            mu[i] = 0;
        }
    }
}
