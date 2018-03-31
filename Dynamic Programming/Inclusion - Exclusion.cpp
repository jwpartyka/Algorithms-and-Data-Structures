// Example of usage of the inclusion - exclusion principle.
// 1) Add a number v to a multiset
// 2) Erase a number v from the multiset
// 3) Count numbers in the multiset which are coprime to v
// Complexity of each query: O(2 ^ (number of distinct prime factors of v))
// Usage: [CF Round #305] Mike and Foam http://codeforces.com/problemset/problem/547/C

using ll = long long;

const int MAXN = 5e5 + 5;

int d[MAXN], mu[MAXN]; // d[i] - number of numbers in the multiset divisible by i,  mu[] - Mobius Function
ll coprime; // Number of coprime pairs of numbers in the multiset
vector<int> p[MAXN]; // p[i] - List of prime divisors of i

// Computes prime factors and Mobius Function of numbers from range [1, n]
void sieve(int n)
{
    for (int i = 1; i <= n; i++)
    {
        mu[i] = i;
    }

    for (int i = 2; i <= n; i++)
    {
        if (p[i].empty())
        {
            for (int j = i; j <= n; j += i)
            {
                p[j].push_back(i);
                mu[j] /= -i;
            }
        }
    }
}

// Counts numbers in the multiset which are coprime to v
int solve(int v, int co)
{
    ll sum = 0;
    for (int mask = 0; mask < (1 << p[v].size()); mask++)
    {
        int x = 1;
        for (int j = 0; j < p[v].size(); j++)
        {
            if (mask & (1 << j)) x *= p[v][j];
        }
        if (co == -1) d[x] += co;
        sum += d[x] * mu[x];
        if (co == 1) d[x] += co;
    }
    return sum;
}

// Adds a number v to the multiset
inline void add(int v)
{
    coprime += solve(v, 1);
}

// Erases a number v from the multiset
inline void erase(int v)
{
    coprime -= solve(v, -1);
}
