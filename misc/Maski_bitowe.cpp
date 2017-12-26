bool bit(int mask, int i)
{
    return (mask & (1<<i));
}
int zapal(int mask, int i)
{
    return (mask | (1<<i));
}
int zgas(int mask, int i)
{
    return ((mask | (1<<i)) ^ (1<<i));
}
int flip(int mask, int i)
{
    return (mask ^ (1<<i));
}
int countOnes(int mask)
{
    return __builtin_popcount(mask);
}
int countZeros(int mask)
{
    return  32 - countOnes(mask);
}
int zeraWiodace(int mask)
{
    return __builtin_clz(mask);
}
int zeraNaKoncu(int mask)
{
    return (mask & (-mask));
    return __builtin_ctz(mask);
}
int smaller2power(int x)
{
    return 30 - zeraWiodace(x);
}
