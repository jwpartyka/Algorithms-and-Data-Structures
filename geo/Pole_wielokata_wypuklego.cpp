//Obliczanie pola wielokąta wypukłego.
//Wektor P przechowuje wierzchołki wielokąta w kierunku przeciwnym do ruchu wskazówek zegara.
//Pole wielokąta to suma iloczynów wektorowych kolejnych wierzchołków podzielona przez 2.

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
