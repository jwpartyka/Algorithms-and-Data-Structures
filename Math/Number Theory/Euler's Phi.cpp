// Euler's Phi
// Phi(n) = number of such numbers a that 1 <= a <= n and gcd (a, n) = 1
// 1) p is prime => Phi(p) = p-1, Phi(p^k) = p^k - p^(k-1)
// 2) (gcd(a, b) = 1) => Phi(a*b) = Phi(a) * Phi(b)
// 3) n = p1^a1 * p2^a2 * ... * pk^ak
//   Phi(n) = Phi(p1^a1) * Phi(p2^a2) * ... * Phi(pk^ak) =
//          = (p1^a1 - p1^(a1-1)) * (p2^a2 - p2^(a2-1)) * ... * (pk^ak - pk^(ak-1)) =
//          = p1^(a1-1) * (p1 - 1) * p2^(a2-1) * (p2 - 1) * ... * pk^(ak-1) * (pk - 1) =
//          = p1^a1 * (1 - 1/p1) * p2^a2 * (1 - 1/p2) * ... * pk^ak * (1 - 1/pk) =
//          = n * ((p1 - 1) / p1) * ((p2 - 1) / p2) * ... * ((pk - 1) / pk) =
//          = (n / (p1 * p2 * ... * pk)) * (p1 - 1) * (p2 - 1) * ... * (pk - 1)

const int MAXN = 1e7+5;

int phi[MAXN], sieve[MAXN];

void EulerPhi(int n)
{
    for (int i = 1; i <= n; i++)
    {
        phi[i] = i;
    }

    for (int i = 2; i <= n; i++)
    {
        if (phi[i] == i)
        {
            for (int j = i; j <= n; j += i)
            {
                phi[j] = phi[j] / i * (i - 1);
            }
        }
    }
}
