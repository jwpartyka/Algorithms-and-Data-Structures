//Dla pary (a, b) zwraca taką parę (x, y), że a*x + b*y = NWD(a, b)

pair<int, int> ExtGCD(int a, int b)
{
    if (a == 0) return {0, 1};
    auto p = ExtGCD(b%a, a);
    return {p.nd - p.st * (b/a), p.st};
}
