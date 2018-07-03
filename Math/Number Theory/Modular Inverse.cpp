// Computing modular multiplicative inverse of a mod m using Euler's theorem:
// a * (a ^ (m - 2)) == 1 mod m
// Complexity: O(log m)

// Computing modular multiplicative inverse of a mod m using Extended Euclid:
// ax + my == gcd(a, m)
// ax == 1 mod m
// Complexity: O(log a)

//Source: Wikipedia

using ll = long long

#define st first
#define nd second

// Euler's theorem:
int modPow(int a, int b, int mod)
{
    if (b <= 0) return 1;
    if (b & 1) return ((ll)a * modPow(a, b - 1, mod)) % mod;
    int c = modPow(a, b / 2, mod);
    return ((ll)c * c) % mod;
}

int modInv(int a, int mod)
{
    return modPow(a, mod - 2);
}

// Extended Euclid:
pair<int, int> ExtGCD(int a, int b)
{
    if (a == 0) return {0, 1};
    auto p = ExtGCD(b % a, a);
    return {p.nd - p.st * (b / a), p.st};
}

int modInv(int a, int mod)
{
    auto p = ExtGCD(a, mod);
    return p.st;
}

int divide(int a, int b, int mod)
{
    return ((ll)a * modInv(b, mod)) % mod;
}
