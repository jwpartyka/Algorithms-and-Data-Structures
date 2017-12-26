//Najdłuższy rosnący podciąg
//Złożoność: O(N * logN)
//Jeżeli potrzebna tylko długość to można zwrócić LIS.size() po pętli for

const int MAXN = 5e5+5, INF = 1e9;

int tab[MAXN];
vector<int> LIS;
int poprz[MAXN], pos[MAXN];

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
        poprz[i] = pos[it - 1];
    }

    int x = pos[LIS.size() - 1];
    LIS.clear();
    while (x)
    {
        LIS.push_back(tab[x]);
        x = poprz[x];
    }
    reverse(LIS.begin(), LIS.end());
    return LIS;
}
