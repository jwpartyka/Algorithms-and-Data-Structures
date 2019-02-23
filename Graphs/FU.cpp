// FU - Find Union / FU - Disjont Set-Union
// 1) Uniting two sets: Union(a, b)
// 2) Finding the head of a set: Find(a, b)
// Complexity: O(alfa(N))
// Usage: [XIV POI] The Flood https://szkopul.edu.pl/problemset/problem/VutzcR1iPvGuYRGZgvNksmV1/site/?key=statement
//        [VI POI] Water https://szkopul.edu.pl/problemset/problem/unBcdJ_-RiRKv0h2PFrgkgzN/site/?key=statement
//        [XXV POI] The Flood

const int MAXN = 1e6 + 5;

struct fu {
    int head, sz;
};

fu FU[MAXN];

inline void MakeSet(int a) {
    FU[a] = {a, 1};
}

int Find(int a) {
    if (FU[a].head != a) {
        FU[a].head = Find(FU[a].head);
    }
    return FU[a].head;
}

inline void Union(int a, int b) {
    a = Find(a);
    b = Find(b);

    if (a == b) {
        return;
    }

    if (FU[a].sz < FU[b].sz) {
        swap(a, b);
    }
    FU[b].head = a;
    FU[a].sz += FU[b].sz;
}
