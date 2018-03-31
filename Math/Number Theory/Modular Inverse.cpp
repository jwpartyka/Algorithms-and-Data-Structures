// Computing modular multiplication inverse of a mod m using Euler's theorem:
// a * (a ^ (m - 2)) == 1 mod m
// Complexity: O(log a)

// Computing modular multiplication inverse of a mod m using Extended Euclid:
// ax + my == gcd(a, m)
// ax == 1 mod m
// Complexity: O(log a)

//Source: Wikipedia

using ll = long long

#define st first
#define nd second

// Euler's theorem:
int pow(int a, int k, int mod)
{
    if (k == 1) return a % mod;
    if (k & 1) return (a * pow(a, k - 1, mod)) % mod;
    int b = pow(a, k / 2, mod);
    return (b * b) % mod;
}

int getInverse(int a, int mod)
{
    return pow(a, mod - 2);
}

// Extended Euclid:
pair<int, int> ExtGCD(int a, int b)
{
    if (a == 0) return {0, 1};
    auto p = ExtGCD(b % a, a);
    return {p.nd - p.st * (b / a), p.st};
}

int getInverse(int a, int mod)
{
    auto p = ExtGCD(a, mod);
    return p.st;
}

int multiply(int a, int b, int mod)
{
    return (ll)((ll)a * getInverse(b, mod)) % mod;
}
