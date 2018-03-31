// Checks whether point p lays inside or on an edge of a convex polygon P
// Points in vector P must be in clockwise or counterclockwise order
// Returns:
// 0) Outside
// 1) On an edge
// 2) Inside
// Complexity: O(log |P|)
// Usage: [USACO 2014 January] Cow curling http://www.usaco.org/index.php?page=viewproblem2&cpid=382

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

int check(vector<point> &P, point p)
{
    int lo = 1, hi = P.size() - 1;
    // If points are in counterclockwise order then reverse them:
    if (cross(P[0], P[lo], P[hi]) > 0) swap(lo, hi);
    // If point p lays to the left of the first edge or to the right of the last edge:
    if (cross(P[0], P[lo], p) > 0 || cross(P[0], P[hi], p) < 0) return 0;
    while (abs(hi - lo) > 1)
    {
        int mid = (lo + hi) / 2;
        if (cross(P[0], P[mid], p) <= 0) lo = mid;
        else hi = mid;
    }

    // If point p lays on an edge (P[lo], P[hi])
    if (cross(P[lo], P[hi], p) == 0) return 1;
    // If point p lays inside triangle (P[lo], P[hi], p)
    if (cross(P[lo], P[hi], p) < 0) return 2;
    return 0;
}
