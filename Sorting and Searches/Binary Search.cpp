int lower_bound(int x)
{
    int l = 0, r = n - 1;
    while (r - l > 1)
    {
        int mid = (l + r) / 2;
        if (tab[i] < x) l = mid;
        else r = mid;
    }
    if (tab[l] >= x) return l;
    if (tab[r] >= x) return r;
    return n;
}

int upper_bound(int x)
{
    int l = 0, r = n - 1;
    while (r - l > 1)
    {
        int mid = (l + r) / 2;
        if (tab[i] <= x) l = mid;
        else r = mid;
    }
    if (tab[l] > x) return l;
    if (tab[r] > x) return r;
    return n;
}

const type EPS = ;
type bin_search()
{
    type l = 0, r = INF;
    while (r - l > EPS)
    {
        type mid = (l + r) / 2;
        if (check(mid)) l = mid;
        else r = mid;
    }
    if (check(l)) return l;
    if (check(r)) return r;
    return INF;
}
