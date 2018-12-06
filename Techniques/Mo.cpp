//Usage: [Yandex.Algorithm 2011 Round 2] Powerful Array http://codeforces.com/problemset/problem/86/D

const int MAXN = 3e5+5;
constexpr int SQRT = 550;

struct query
{
    int x, y, pos, res;
    short sqrt;
    bool operator < (const query &b) const
	{
		if (sqrt == b.sqrt)
		{
		    if (y == b.y) return pos < b.pos;
		    return ((sqrt & 1) ^ (y < b.y));
		}
		return x > b.x;
	}
};

int res[MAXN];
query que[MAXN];

inline void dodaj(int i, int j, int op)
{
    /* Updates values */
}

inline void update(int i, int a, int b)
{
    int op = 1;
    if (a < b) op = -1;
    else swap(a, b);
    for (int j = a; j < b; j++)
    {
        dodaj(i, j, op);
    }
}

void solve(int q)
{
    for (int i = 0; i < q; i++)
    {
        que[i].pos = i;
        que[i].sqrt = que[i].x / SQRT;
    }

    sort(que, que + q);

    int x = que[0].x, y = que[0].y;
    for (int i = x; i <= y; i++)
    {
        dodaj(0, i, 1);
    }
    res[que[0].pos] = que[0].res;

    for (int i = 1; i < q; i++)
    {
        que[i].res = que[i - 1].res;
        update(i, x, que[i].x);
        update(i, que[i].y, y);
        x = que[i].x, y = que[i].y;
        res[que[i].pos] = que[i].res;
    }

    for (int i = 0; i < q; i++)
    {
        cout << res[i];
    }
}
