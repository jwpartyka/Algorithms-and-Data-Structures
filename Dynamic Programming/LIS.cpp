// Longest Increasing Subsequence
// Complexity: O(N * log N)
// If only the length of the LIS is needed you can return LIS.size() after the 'for' loop.

const int MAXN = 5e5+5, inf = 1e9;

int tab[MAXN];
vector<int> LIS;
int prev[MAXN], pos[MAXN];

int lower_bound(int l, int r, int x)
{
    while (r-l > 1)
    {
        int mid = (l + r) / 2;
        if (LIS[mid] < x) l = mid;
        else r = mid;
    }
    if (LIS[l] >= x) return l;
    else if (LIS[r] >= x) return r;
    return r + 1;
}

vector<int> calcLIS(int n)
{
    LIS.push_back(-INF);
    for (int i = 1; i <= n; i++)
    {
        int it = lower_bound(0, LIS.size() - 1, tab[i]);
        if (it == LIS.size())
        {
            LIS.push_back(tab[i]);
        }
        else LIS[it] = tab[i];
        pos[it] = i;
        prev[i] = pos[it - 1];
    }

    //return LIS.size();
    
    int x = pos[LIS.size() - 1];
    LIS.clear();
    while (x)
    {
        LIS.push_back(tab[x]);
        x = prev[x];
    }
    reverse(LIS.begin(), LIS.end());
    return LIS;
}
