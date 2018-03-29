//Znajduje otoczkę wypukłą algorytmem Grahama.
//Żadne 3 wierzchołki otoczki nie są współliniowe.
//Wierzchołki otoczki są ułożone przeciwnie do ruchu wskazówek zegara.
//Złożoność: O(N * log N)
//Source: USACO

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

ll norm(point a)
{
    return a.x * a.x + a.y * a.y;
}

vector<point> getHull(vector<point> &P)
{
    vector<point> H = {P[0]};
    int sz = 1;
    for (int i = 1; i < P.size(); i++)
    {
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

vector<point> Graham(vector<point> P)
{
    swap(P[0], *min_element(P.begin(), P.end(), [](point a, point b)
    {
        if (a.x == b.x) return a.y < b.y;
        return a.x < b.x;
    }));
    sort(P.begin() + 1, P.end(), [&P](point a, point b)
    {
        ll cr = cross(P[0], a, b);
        if (cr == 0) return norm(a - P[0]) < norm(b - P[0]);
        return cr > 0;
    });
    P.erase(unique(P.begin(), P.end(), [](point a, point b)
    {
        return (a.x == b.x and a.y == b.y);
    }), P.end());

    auto H = getHull(P);

    return H;
}
