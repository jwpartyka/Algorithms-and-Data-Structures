int NWD(int a, int b)
{
    if (a == 0) return b;
    return NWD(b%a, a);
}
