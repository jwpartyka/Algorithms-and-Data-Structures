// Computing the total area of a simple polygon P
// Points in vector P must be in counterclockwise order. If they're not then multiply the answer by -1.
// The total area is a sum of cross products of each pair of consecutive edges divided by 2.
// Usage: [SPOJ] CALCAREA http://www.spoj.com/problems/CALCAREA/
using ll = long long;

struct point
{
    int x, y;
    ll operator * (const point &b) const
    {
        return (ll)x * (ll)b.y - (ll)y * (ll)b.x;
    }
};

double Area(vector<point> &P)
{
    ll area = 0;
    for (int i = 0; i < P.size() - 1; i++)
    {
        area += P[i] * P[i + 1];
    }
    area += P.back() * P.front();
    return (double)area / 2.;
}
