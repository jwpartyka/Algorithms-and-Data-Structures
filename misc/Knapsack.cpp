//Algorytm plecakowy
//Złożoność O(N^2)

const int MAXN = 1e3+5;

struct przedmiot
{
    int w, c; //waga i cena przedmiotu
    bool operator<(przedmiot const &b)const
    {
        if (w == b.w) return c < b.c;
        return w < b.w;
    }
};

przedmiot item[MAXN];
int sack[MAXN];

int knapsack(int n, int k)
{
    sort(item, item+n);
    for (int i = 0; i < n; i++)
    {
        for (int j = k - item[i].w; j >= 0; j--)
        {
            if (sack[j] || j == 0)
            {
                sack[j + item[i].w] = max(sack[j + item[i].w], sack[j] + item[i].c);
            }
        }
    }

    int res = 0;
    for (int i = 1; i <= k; i++)
    {
        res = max(res, sack[i]);
    }
    return res;
}
