// Divide & Conquer Optimization
// Run dnc(k, k, n, k - 1, n) for 1 <= k <= K
// Complexity:
// O(K * nlogn)

using ll = long long;

const int MAXN = 1e5 + 5, MAXK = 55;

int Opt[MAXK][MAXN];
ll dp[MAXK][MAXN];

ll C(int l, int r) {
    return 0;
}

void dnc(int i, int l, int r, int optl, int optr) {
    if (l > r) {
        return;
    }

    int mid = (l + r) / 2;
    int opt = optl;
    for (int j = optl; j <= min(mid - 1, optr); j++) {
        if (dp[i - 1][j] + C(j + 1, mid) > dp[i][mid]) {
            dp[i][mid] = dp[i - 1][j] + C(j + 1, mid);
            opt = j;
        }
    }
    Opt[i][mid] = opt;

    dnc(i, l, mid - 1, optl, opt);
    dnc(i, mid + 1, r, opt, optr);
}

