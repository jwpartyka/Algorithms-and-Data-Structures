//Znajduje otoczkę wypukłą algorytmem Grahama

using ll = long long;

const int MAXN = 1e6 + 5;

struct point
{
    int x, y, id;

    point operator - (const point &b) const
    {
        return {x - b.x, y - b.y};
    }

    ll operator * (const point &b) const
    {
        return (ll)x * (ll)b.y - (ll)y * (ll)b.x;
    }
};

int CH[MAXN];
point tab[MAXN], p0;

bool cmp1(point a, point b)
{
    if (a.y == b.y)
    {
        return a.x < b.x;
    }
    return a.y < b.y;
}

bool cmp2(point a, point b)
{
    return (a - p0) * (b - p0) > 0;
}

bool w_prawo(int a, int b, int c)
{
    return (tab[b] - tab[a]) * (tab[c] - tab[a]) < 0;
}

int ConvexHull(vector<point> &P)
{
    sort(P.begin(), P.end(), cmp1);
    p0 = P[0];
    sort(P.begin() + 1, P.end(), cmp2);

    if (P.size() <= 3)
    {
        for (int i = 0; i < P.size(); i++)
        {
            CH[i] = P[i].id;
        }
        return P.size();
    }

    P.push_back(P[0]);
    CH[0] = P[0].id;
    CH[1] = P[1].id;
    int sz = 2;
    for (int i = 2; i < P.size(); i++)
    {
        while (w_prawo(CH[sz - 2], CH[sz - 1], P[i].id))
        {
            sz--;
        }
        CH[sz] = P[i].id;
        sz++;
    }
    sz--;
    return sz;
}

int getHull(int n)
{
    vector<point> P;
    for (int i = 1; i <= n; i++)
    {
        P.push_back(tab[i]);
    }
    int sz = ConvexHull(P);
    for (int i = 0; i < sz; i++)
    {
        cout << tab[CH[i]].x << " " << tab[CH[i]].y << "\n";
    }
    return sz;
}
