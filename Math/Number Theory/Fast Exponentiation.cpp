// Fast exponentation a ^ b
// Complexity: O(log b)

// Recursive
int pow(int a, int b)
{
    if (b <= 0) return 1;
    if (b & 1) return a * pow(a, b - 1);
    int c = pow(a, b / 2);
    return c * c;
}

// Iterative
int pow(int a, int b)
{
    int res = 1;
    while (b)
    {
        if (b & 1) res *= a;
        b /= 2;
        a *= a;
    }
    return res;
}
