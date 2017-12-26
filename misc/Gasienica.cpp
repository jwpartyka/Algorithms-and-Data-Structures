//Dany jest cykl. Podziel go dwoma cięciami na dwa niepuste fragmenty o minimalnej
//różnicy sumy elementów.

#include <iostream>

using namespace std;
using ll = long long;

const int MAXN = 2e6+5;

int tab[MAXN];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    ll SUM = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> tab[i];
        tab[i + n] = tab[i];
        SUM += tab[i];
    }

    int r = 0;
    ll sum = 0, res = 0;
    for (int l = 0; l < n; l++)
    {
        while (r - l < n && 2 * sum <= SUM)
        {
            res = max(res, sum);
            sum += tab[r];
            r++;
        }
        sum -= tab[l];
    }
    cout << res << "\n";
}
