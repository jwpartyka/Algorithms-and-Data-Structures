// Parametric Search
// Run ParametricSearch(k)

using ll = long long;
using ld = long double;

#define st first
#define nd second

const int MAXN = 3e5 + 5;
const ll INF = 1e12;

// (f(best), best)
pair<ll, int> check(ld alfa) {
    return {0, 0};
}

ll ParametricSearch(int k) {
    ll lo = -INF, hi = INF;
    while (hi - lo > 1) {
        ll mid = (lo + hi) / 2;
        if (check(mid).nd < k) {
            hi = mid;
        } else {
            lo = mid;
        }
    }
    auto res = check(hi);
    ll alfa = hi;
    if (res.nd < k) {
        res = check(lo);
        alfa = lo;
    }

    return res.st + k * alfa;
}
