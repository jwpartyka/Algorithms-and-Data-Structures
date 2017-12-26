//Merge merge
//Złożoność: O(N * logN)

const int MAXN = 5e5+5;

int tab[MAXN];

void merge(int l, int r)
{
    int mid = (l + r) / 2;
    vector<int> tmp;
    int x = l, y = mid + 1;
    while (x <= mid || y <= r)
    {
        if (x > mid || (y <= r && tab[y] < tab[x]))
        {
            tmp.push_back(tab[y]);
            y++;
        }
        else
        {
            tmp.push_back(tab[x]);
            x++;
        }
    }

    for (int i = 0; i < tmp.size(); i++)
    {
        tab[l + i] = tmp[i];
    }
}
void mergeSort(int l, int r)
{
    if (l == r) return ;
    mergeSort(l, (l + r) / 2);
    mergeSort((l + r) / 2 + 1, r);
    merge(l, r);
}
