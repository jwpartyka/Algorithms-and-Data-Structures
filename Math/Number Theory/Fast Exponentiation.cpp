// Fast exponentation a ^ k
// Complexity: O(log a)

// Recursive
int pow(int a, int k)
{
    if (k == 1) return a;
    if (k & 1) return a * pow(a, k - 1);
    int b = pow(a, k / 2);
    return b * b;
}

// Iterative
int pow(int a, int k)
{
    int res = 1;
    while (k)
    {
        if (k & 1) res *= a;
        k /= 2;
        a *= a;
    }
    return res;
}
