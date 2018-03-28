//Znajduje otoczkę wypukłą algorytmem Jarvisa.
//Jak są trzy punkty współliniowe to się psuje.
//Złożoność: O(N * log N)

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

//Wyznacza część otoczki:
inline void getPart(vector<point> &P, vector<point> &H)
{
    H.push_back(P[0]);
    int sz = H.size();
    for (int i = 1; i < P.size(); i++)
    {
        while (sz >= 2 && cross(H[sz - 2], H[sz - 1], P[i]) > 0)
        {
            sz--;
            H.pop_back();
        }
        sz++;
        H.push_back(P[i]);
    }

    H.pop_back();
}

//Zwraca otoczkę
vector<point> getHull(vector<point> &P)
{
    vector<point> H;

    //Sortuje malejąco punkty (x, y)
    sort(P.begin(), P.end(), [](point a, point b)
    {
        if (a.X == b.X) return a.Y < b.Y;
        return a.X < b.X;
    });

    //Znajduje górną otoczkę:
    getPart(P, H);

    //Sortuje rosnąco punkty (x, y)
    sort(P.begin(), P.end(), [](point a, point b)
    {
        if (a.X == b.X) return a.Y > b.Y;
        return a.X > b.X;
    });

    //Znajduje dolną otoczkę:
    getPart(P, H);

    return H;
}
