//Sortowanie kątowe względem środka układu współrzędnych.
//Najpierw sortuje punkty, które mają y >= 0, później resztę.
//Na koniec łączy oba wektory.

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;

const int MAXN = 1e6+5;

struct point
{
    int x, y;
};

bool cmp(point a, point b)
{
    return (ll)((ll)a.x * (ll)b.y) - (ll)((ll)a.y * (ll)b.x);
}

point tab[MAXN];
vector<point> V[2];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        V[(y < 0)].push_back({x, y});
    }

    sort(V[0].begin(), V[0].end(), cmp);
    sort(V[1].begin(), V[1].end(), cmp);

    int num = 0;
    for (int i = 0; i < 2; i++)
    {
        for (auto p : V[i])
        {
            tab[num] = p;
            num++;
        }
        V[i].clear();
    }
}
