//Sortowanie kątowe względem punktu o najmniejszym y, a jeżeli jest takich wiele
//to względem tego z nich o najmniejszym x.

#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;

const int MAXN = 1e6+5;

struct point
{
    int x, y;
};

point p0, tab[MAXN];

//Sortuje najpierw po y, później po x
bool cmp1(point a, point b)
{
    if (a.y == b.y)
    {
        return a.x < b.x;
    }
    return a.y < b.y;
}

//Sortuje kątowo
bool cmp2(point a, point b)
{
    return (ll)(a.x - p0.x) * (ll)(b.y - p0.y) - (ll)(b.x - p0.x) * (ll)(a.y - p0.y) >= 0;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> tab[i].x >> tab[i].y;
    }

    sort(tab, tab + n, cmp1);
    p0 = tab[0];
    sort(tab + 1, tab + n, cmp2);
}
