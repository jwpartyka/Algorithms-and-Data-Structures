//Sito eratostenesa
//Złożoność: O(N * loglogN)
//Rozkład na czynnkiki pierwsze w O(logN)

const int MAXN = 1e6+5;

int sieve[MAXN], sum[MAXN];

//Liczenie sita
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

//Liczba liczb pierwszych z przedziału [l, r]
int countPrimes(int l, int r)
{
    return sum[r] - sum[l - 1];
}

//Zwraca wektor z rozkładem x na czynniki pierwszse
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
