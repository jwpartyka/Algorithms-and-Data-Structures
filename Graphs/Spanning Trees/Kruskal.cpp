// Kruskal's algorithm for finding MST
// It uses FU
// Complexity O(|E| * log |E|)
// Usage: [SPOJ] MST http://www.spoj.com/problems/MST/

const int MAXN = 1e6 + 5;

struct edge {
    int v, u, w;
};

vector<edge> E; // List of edges (v, u) with weight w
vector<pair<int, int>> MST[MAXN];

void findMST(int n) {
    for (int i = 1; i <= n; i++) {
        MakeSet(i);
    }

    sort(E.begin(), E.end(), [](edge a, edge b) {
        return a.w < b.w;
    });

    for (auto e : E) {
        int v = Find(e.v), u = Find(e.u);
        if (v != u) {
            Union(v, u);
            MST[v].push_back({u, e.w});
            MST[u].push_back({v, e.w});
        }
    }
}
