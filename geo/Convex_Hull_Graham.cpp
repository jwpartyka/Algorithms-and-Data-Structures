//Znajduje otoczkę wypukłą algorytmem Grahama.
//Żadne 3 wierzchołki otoczki nie są współliniowe.
//Wierzchołki otoczki są posortowane zgodnie z ruchem wskazówek zegara.
//Złożoność: O(N * log N)
//Source: USACO

using ll = long long;
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

//Zwraca otoczkę
vector<point> getHull(vector<point> P)
{
    //Znajduje punkt o minimalnym x, y
    swap(P[0], *min_element(P.begin(), P.end(), [](point a, point b)
    {
        if (a.X == b.X) return a.Y < b.Y;
        return a.X < b.X;
    }));
    //Sortuje kątowo
    sort(P.begin() + 1, P.end(), [&P](point a, point b)
    {
        ll cr = cross(P[0], a, b);
        if (cr != 0) return cr < 0;
        return abs(a - P[0]) < abs(b - P[0]);
    });

    //Znajduje otoczkę:
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
