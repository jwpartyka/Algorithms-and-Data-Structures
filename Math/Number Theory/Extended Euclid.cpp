// For pair (a, b) returns such pair (x, y) that ax + by = gcd(a, b)
// Complexity: O(log min(a, b))

#define st first
#define nd second

pair<int, int> ExtGCD(int a, int b)
{
    if (a == 0) return {0, 1};
    auto p = ExtGCD(b % a, a);
    return {p.nd - p.st * (b / a), p.st};
}
