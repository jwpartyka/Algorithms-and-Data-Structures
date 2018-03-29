//Znajduje otoczkę wypukłą algorytmem Andrew.
//Złożoność: O(N * log N)
//Source: Benjamin Qi

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

//Znajduje część otoczki
vector<point> getHull(vector<point> &P)
{
    vector<point> H = {P[0]};
    int sz = 1;
    for (int i = 1; i < P.size(); i++)
    {
        //Jeżeli mogą być współliniowe boki na otoczce to zmienić: cross() < 0
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

//Zwraca całą otoczkę
vector<point> Andrew(vector<point> P)
{
    //Sortuje malejąco punkty
    sort(P.begin(), P.end(), [](point a, point b)
    {
        if (a.x == b.x) return a.y < b.y;
        return a.x < b.x;
    });
    //Usuwa kopie punktów
    P.erase(unique(P.begin(), P.end(), [](point a, point b)
    {
        return (a.x == b.x and a.y == b.y);
    }), P.end());
    if (P.size() == 1) return P;

    //Znajduje dolną otoczkę
    auto low = getHull(P);
    low.pop_back();

    //Sortuje rosnąco punkty
    reverse(P.begin(), P.end());

    //Znajduje górną otoczkę
    auto up = getHull(P);
    up.pop_back();

    //Łączy otoczki
    for (auto p : up) low.push_back(p);

    return low;
}
