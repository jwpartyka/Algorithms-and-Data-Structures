//Funkcja phi Eulera:
//Phi(n) = liczba takich a, że 1 <= a <= n oraz NWD(a, n) = 1
//1) p jest pierwsze => Phi(p) = p-1, Phi(p^k) = p^k - p^(k-1)
//2) NWD(a, b) = 1 => Phi(a*b) = Phi(a) * Phi(b)
//3) n = p1^a1 * p2^a2 * ... * pk^ak
//   Phi(n) = Phi(p1^a1) * Phi(p2^a2) * ... * Phi(pk^ak) =
//          = (p1^a1 - p1^(a1-1)) * (p2^a2 - p2^(a2-1)) * ... * (pk^ak - pk^(ak-1)) =
//          = p1^(a1-1) * (p1 - 1) * p2^(a2-1) * (p2 - 1) * ... * pk^(ak-1) * (pk - 1)

const int MAXN = 1e7+5;

int phi[MAXN], sieve[MAXN];

void EulerPhi(int n)
{
    for (int i = 1; i <= n; i++)
    {
        phi[i] = 1;
    }

    for (int i = 2; i <= n; i++)
    {
        if (!sieve[i])
        {
            phi[i] = i-1;
            for (int j = 2 * i; j <= n; j += i)
            {
                if (!sieve[j]) sieve[j] = i;
                int p = 1;
                while (j % (p * i * i) == 0)
                {
                    p *= i;
                }
                phi[j] *= (p * (i - 1));
            }
        }
    }
}
