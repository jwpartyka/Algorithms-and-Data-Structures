//Usage: [Yandex.Algorithm 2011 Round 2] Powerful Array http://codeforces.com/problemset/problem/86/D
 
const int MAXN = 1e5 + 5, SQRT = 100;

struct query {
    int x, y, id, res;
    short sq;

    bool operator <(const query &b) const {
        if (sq == b.sq) {
            if (y == b.y) {
                return id < b.id;
            }
            return ((sq & 1) ^ (y < b.y));
        }
        return x > b.x;
    }
};

int res[MAXN];
query que[MAXN];

inline void modify(int a, int v) {
    /* ... */
}

inline void update(int a, int b, int v) {
    for (int i = a; i <= b; i++) {
         modify(i, v);
    }
}

void Mo(int q) {
    sort(que, que + q);
    int x = 0, y = -1;
    for (int i = 0; i < q; i++) {
        if (que[i].x > x) {
            update(x, que[i].x - 1, -1);
        }
        else {
            update(que[i].x, x - 1, 1);
        }

        if (que[i].y > y) {
            update(y + 1, que[i].y, 1);
        }
        else {
            update(que[i].y + 1, y, -1);
        }

        res[que[i].id] = que[i].res;
        x = que[i].x, y = que[i].y;
    }
}
