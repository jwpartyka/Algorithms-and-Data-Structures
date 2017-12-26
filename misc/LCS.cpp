//Najdłuższe wspólny podciąg dwóch słów
//Jeżeli potrzebna tylko długość to można zwrócić LCS[n][m] po pierwszych dwóch pętlach for
//Złożoność O(N^2)

const int MAXN = 5e3+5;
int LCS[MAXN][MAXN];

string calcLCS(string a, string b, int n, int m)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            LCS[i][j] = max(LCS[i - 1][j], LCS[i][j - 1]);
            if (a[i - 1] == b[j - 1])
            {
                LCS[i][j] = LCS[i - 1][j - 1] + 1;
            }
        }
    }


    string res;
    int x = n, y = m;
    while (x && y)
    {
        if (a[x - 1] == b[y - 1])
        {
            res += a[x - 1];
            x--, y--;
        }
        else
        {
            LCS[ x- 1][y] > LCS[x][y - 1] ? x-- : y--;
        }
    }
    reverse(res.begin(), res.end());
    return res;
}
