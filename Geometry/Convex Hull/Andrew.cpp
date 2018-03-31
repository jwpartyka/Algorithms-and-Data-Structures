// Finds convex hull of a set P of points using Andrew's Algorithm.
// Points on convex hull are in counterclockwise order
// Complexity: O(N * log N)
// Source: Benjamin Qi
// Usage: [Kattis] Convex Hull https://open.kattis.com/problems/convexhull

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

    inline bool operator < (const point &b) const
    {
        if (a.x == b.x) return a.y < b.y;
        return a.x < b.x;
    }

    inline bool operator == (const point &b) const
    {
        return (a.x == b.x and a.y == b.y);
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

// Finds a part of the hull.
vector<point> getHull(vector<point> &P)
{
    vector<point> H = {P[0]};
    int sz = 1;
    for (int i = 1; i < P.size(); i++)
    {
        // If colinear segments are allowed to be on the hull: cross() < 0
        while (sz >= 2 && cross(H[sz - 2], H.back(), P[i]) <= 0)
        {
            sz--;
            H.pop_back();
        }
        sz++;
        H.push_back(P[i]);
    }
    return H;
}

// Returns convex hull
vector<point> Jarvis(vector<point> P)
{
    // Sorts points lexicographically
    sort(P.begin(), P.end());

    // Erases duplicates
    P.erase(unique(P.begin(), P.end()), P.end());
    if (P.size() == 1) return P;

    // Finds the lower hull
    auto low = getHull(P);
    low.pop_back();

    // Reverses lexicographically sorted list of points
    reverse(P.begin(), P.end());

    // Finds the upper hull
    auto up = getHull(P);
    up.pop_back();

    // Merges both parts of the hull
    for (auto p : up) low.push_back(p);

    return low;
}
