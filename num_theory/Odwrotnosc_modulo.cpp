//Liczenie odwrotności modulo z małego twierdzenia Fermata
//a^(p - 1) = 1 (mod p)
//a * a^(p - 2) = 1 (mod p) => a^(p - 2) jest odwrotnością a (mod p)

using ll = long long;

constexpr int mod = 1e9 + 7;

int fpow(int a, int k)
{
    if (k == 1) return a % mod;
    if (k & 1) return (ll)((ll)a * (ll)fpow(a, k - 1)) % mod;
    int b = fpow(a, k / 2);
    return (ll)((ll)b * (ll)b) % mod;
}

int podziel(int a, int b)
{
    return (ll)((ll)a * (ll)fpow(b, mod - 2)) % mod;
}
