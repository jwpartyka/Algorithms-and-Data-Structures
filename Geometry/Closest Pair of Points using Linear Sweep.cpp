#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <iomanip>

using namespace std;
using ll = long long;
using ld = double;

const ll INF = 1e18;

struct point
{
    ld x, y;
    int id;
    inline point operator - (const point &b) const
    {
        return {x - b.x, y - b.y};
    }
    inline bool operator < (const point &b) const
    {
        if (x == b.x) return y < b.y;
        return x < b.x;
    }
};

ld norm(point a)
{
    return a.x * a.x + a.y * a.y;
}

ld abs(point a)
{
    return sqrt(norm(a));
}

struct cmp
{
    inline bool operator() (const point &a, const point &b)
    {
        if (a.y == b.y) return a.x < b.x;
        return a.y < b.y;
    }
};

pair<point, point> closestPoints(vector<point> P)
{
    deque<point> Sx;
    set<point, cmp> Sy;

    ld mini = INF;
    sort(P.begin(), P.end());
    point a, b;
    for (auto p : P)
    {
        while (!Sx.empty() and Sx[0].x < p.x - mini)
        {
            Sy.erase(Sx[0]);
            Sx.pop_front();
        }
        auto it = lower_bound(Sy.begin(), Sy.end(), point({p.x - mini, p.y - mini}));
        while (it != Sy.end() && it -> y <= p.y + mini)
        {
            auto pp = *it;
            if (abs(p - pp) < mini)
            {
                mini = abs(p - pp);
                a = pp, b = p;
            }
            mini = min(mini, abs(p - pp));
            it++;
        }

        Sx.push_back(p);
        Sy.insert(p);
    }

    return {a, b};
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    while (true)
    {
        int n;
        cin >> n;
        if (!n) break;
        vector<point> P;
        for (int i = 0; i < n; i++)
        {
            ld x, y;
            cin >> x >> y;
            P.push_back({x, y, i});
        }

        auto [a, b] = closestPoints(P);

        cout << a.x << " " << a.y << " " << b.x << " " << b.y << "\n";
    }
}
