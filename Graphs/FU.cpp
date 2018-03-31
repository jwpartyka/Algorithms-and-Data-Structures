// FU - Find Union or DSU - Disjont Set - Union
// 1) Uniting two sets: UNION(a, b)
// 2) Finding head of a set: FIND(a, b)
// Complexity: O(log* N)
// Usage: [XIV POI] The Flood https://szkopul.edu.pl/problemset/problem/VutzcR1iPvGuYRGZgvNksmV1/site/?key=statement
//        [VI POI] Water https://szkopul.edu.pl/problemset/problem/unBcdJ_-RiRKv0h2PFrgkgzN/site/?key=statement
//        [XXV POI] The Flood

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
