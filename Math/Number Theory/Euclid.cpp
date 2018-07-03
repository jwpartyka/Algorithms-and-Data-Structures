// Complexity: O(log min(a, b))

int gcd(int a, int b)
{
    if (a == 0) return b;
    return gcd(b % a, a);
}
