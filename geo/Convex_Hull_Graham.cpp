//Znajduje otoczkę wypukłą algorytmem Grahama po ówczesnym posortowaniu kątowym.
//Złożoność: O(N * log N)
//Source: USACO

using ll = long long;
//Działanie biblioteki complex dla typów innych niż float, double i long double
//jest niezdefiniowane w standardzie, ale działa.
using point = complex<ll>;

#define X real()
#define Y imag()

ll cross(point a, point b)
{
    return (conj(a) * b).Y;
}

ll cross(point a, point b, point c)
{
    return cross(b - a, c - a);
}

vector<point> getHull(vector<point> P)
{
    swap(P[0], *min_element(P.begin(), P.end(), [](point a, point b)
    {
        if (a.Y == b.Y) return a.X < b.X;
        return a.Y < b.Y;
    }));
    sort(P.begin() + 1, P.end(), [&P](point a, point b)
    {
        ll cr = cross(P[0], a, b);
        if (cr != 0) return cr < 0;
        return abs(a - P[0]) < abs(b - P[0]);
    });

    vector<point> H;
    H.push_back(P[0]);
    int sz = 1;
    for (int i = 1; i < P.size(); i++)
    {
        while (sz >= 2 && cross(H[sz - 2], H[sz - 1], P[i]) >= 0)
        {
            sz--;
            H.pop_back();
        }
        sz++;
        H.push_back(P[i]);
    }
    return H;
}
