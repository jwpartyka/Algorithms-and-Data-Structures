//Znajdywanie minimum funkcji bitonicznej

//Na liczbach całkowitych:
int Ternary_Search(int l, int r)
{
    while (r - l > 3)
    {
        int mid = (l + r) / 2;
        if (f(mid) >= f(mid + 1)) l = mid;
        else r = mid + 1;
    }
    int best = r;
    for (int i = l; i < r; i++)
    {
        if (f(i) < f(best)) best = i;
    }
    return best;
}

//Na liczbach rzeczywistych:
double Ternary_Search(double l, double r)
{
    for (int i = 0; i < 123; i++)
    {
        double midl = l + (r - l) / 3.;
        double midr = r - (r - l) / 3.;
        double f1 = f(midl), f2 = f(midr);
        if (f1 > f2) l = midl;
        else r = midr;
    }
    return (l + r) / 2;
}
