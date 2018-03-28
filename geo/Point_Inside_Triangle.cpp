//Sprawdza, czy punkt p leży wewnątrz trojkąta (a, b, c).

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

bool check(point a, point b, point c, point p)
{
    //Jeżeli boki są w kolejności przeciwnej do ruchu wskazówek zegara to odwróć:
    if (cross(a, b, c) > 0) swap(b, c);
    //Jeżeli punkt leży na lewo od pierwszego boku lub na prawo od ostatniego:
    if (cross(a, b, p) > 0 || cross(a, c, p) < 0) return 0;
    //Czy punkt p leży pomiędzy bokami ab i ac
    return cross(b, c, p) <= 0;
}
