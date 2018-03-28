//Sprawdza, czy punkt p leży wewnątrz lub na bokach wielokąta wypukłego P.
//Wektor P musi mieć listę boków wielokąta P w kolejności ruchu wskazówek zegara lub przeciwnej.
//Złożoność: O(log N)

using ll = long long;
//Działanie biblioteki complex dla typów innych niż float, double i long double
//jest niezdefiniowane w standardzie, ale działa.
using point = complex<ll>;

#define X real()
#define Y img()

ll cross(point a, point b)
{
    return (conj(a) * b).Y;
}

ll cross(point a, point b, point c)
{
    return cross(b - a, c - a);
}

bool check(vector<point> &P, point p)
{
    int lo = 1, hi = P.size() - 1;
    //Jeżeli boki są w kolejności przeciwnej do ruchu wskazówek zegara to odwróć:
    if (cross(P[0], P[lo], P[hi]) > 0) swap(lo, hi);
    //Jeżeli punkt leży na lewo od pierwszego boku lub na prawo od ostatniego:
    if (cross(P[0], P[lo], p) > 0 || cross(P[0], P[hi], p) < 0) return 0;
    while (abs(hi - lo) > 1)
    {
        int mid = (lo + hi) / 2;
        if (cross(P[0], P[mid], p) <= 0) lo = mid;
        else hi = mid;
    }
    //Czy punkt leży w trójkącie (P[0], P[lo], P[hi]):
    return (cross(P[lo], P[hi], p) <= 0);
}
