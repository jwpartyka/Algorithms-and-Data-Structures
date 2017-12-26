//Drzewo potęgowe 2D: dodaj w (x, y), zczytaj sume z [(a, b), (c, d)]
//Złożoność operacji: O(log^2(Base))

const int Base = 1024;

int Tree[Base + 5][Base + 5], Base = 1;

int f(int x)
{
    return x & (-x);
}

void chTreeY(int x, int y, int v)
{
    while (y <= Base)
    {
        Tree[x][y] += v;
        y += f(y);
    }
}
void chTreeX(int x, int y, int v)
{
    while (x <= Base)
    {
        chTreeY(x, y, v);
        x += f(x);
    }
}

int readY(int x, int y)
{
    int res = 0;
    while (y)
    {
        res += Tree[x][y];
        y -= f(y);
    }
    return res;
}
int readX(int x, int y)
{
    int res = 0;
    while (x)
    {
        res += readY(x, y);
        x -= f(x);
    }
    return res;
}

int read(int a, int b, int c, int d)
{
    return readX(c, d) - readX(a-1, d) - readX(c, b-1) + read(a-1, b-1);
}
void chTree(int x, int y, int b)
{
    chTreeX(x, y, v);
}
