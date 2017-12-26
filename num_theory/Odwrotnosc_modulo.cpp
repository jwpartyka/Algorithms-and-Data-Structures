//Liczenie odwrotności modulo z małego twierdzenia Fermata
//a^(p-2) = 1 (mod p)

using ll = long long

int pow(int a, int k, int mod)
{
    if (k == 1) return a % mod;
    if (k & 1) return (a * pow(a, k - 1, mod)) % mod;
    int b = pow(a, k / 2, mod);
    return (b * b) % mod;
}
int multiply(int a, int b, int mod)
{
    return (ll)((ll)a * (ll)pow(b, mod - 2, mod)) % mod;
}
