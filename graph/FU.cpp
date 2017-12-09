//Umożliwia operacje na zbiorach rozłącznych:
//Złączenie dwóch zbiorów (UNION(a, b)), znalezienie reprezentanta zbioru (FIND(a))
//Złożoność jednej operacji: O(log*N)

const int MAXN = 5e5+5;
struct fu
{
    int head, rank;
};
fu FU[MAXN];

void initSet(int a)
{
    FU[a].head = a;
}

int FIND(int a)
{
    if (a != FU[a].head) FU[a].head = FIND(FU[a].head);
    return FU[a].head;
}

void UNION(int a, int b)
{
    a = FIND(a), b = FIND(b);
    if (FU[a].rank < FU[b].rank)
    {
        FU[a].head = b;
    }
    else
    {
        FU[b].head = a;
        if (FU[a].rank == FU[b].rank)
        {
            FU[a].rank++;
        }
    }
}
