// Checks whether point p lays inside a triangle (a, b, c)
// Returns:
// 0) Outside
// 1) On an edge
// 2) Inside
// Complexity: O(1)
// Usage: [SPOJ PL] T_PINTR http://pl.spoj.com/problems/T_PINTR/

using ll = long long;

struct point
{
    ll x, y;

    inline point operator - (const point &b) const
    {
        return {x - b.x, y - b.y};
    }

    inline ll operator * (const point &b) const
    {
        return (x * b.y) - (y * b.x);
    }
};

ll cross(point a, point b)
{
    return a * b;
}

ll cross(point a, point b, point c)
{
    return cross(b - a, c - a);
}

int check(point a, point b, point c, point p)
{
    // If the point are in counterclockwise order then reverse them
    if (cross(a, b, c) > 0) swap(b, c);
    ll cr1 = cross(a, b, p);
    ll cr2 = cross(b, c, p);
    ll cr3 = cross(c, a, p);
    // If p is inside or on an edge
    if (cr1 <= 0 && cr2 <= 0 && cr3 <= 0)
    {
        // If p is on an edge
        if (cr1 == 0 || cr2 == 0 || cr3 == 0) return 1;
        return 2;
    }
    return 0;
}
