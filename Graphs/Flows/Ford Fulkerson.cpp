// Ford - Fulkerson method
//Złożoność: O(maxflow * (|V| + |E|))
// Usage: [SPOJ] FLOW http://www.spoj.com/A12/problems/FLOW/
//        [VI POI] Speleology https://szkopul.edu.pl/problemset/problem/l7RiYCdarLZV51E2daTt4n4W/site/?key=statement

using ll = long long;

#define st first
#define nd second

const int MAXN = 5e3 + 5, inf = 1e9;

int E[MAXN * MAXN], vis[MAXN], n, tgt, id, tim = 1;
vector<pair<int, int>> G[MAXN];

inline void addEdge(int a, int b, int c) {
    G[a].push_back({b, id});
    E[id++] = c;
    G[b].push_back({a, id++});
}

int dfs(int v, int flow) {
    if (v == tgt) {
        return flow;
    }
    vis[v] = tim;

    for (auto e : G[v]) {
        int u = e.st, x = e.nd;
        if (vis[u] == tim) {
            continue;
        }

        int f = E[x];
        if (f) {
            f = dfs(u, min(flow, f));
        }
        if (not f) {
            continue;
        }

        E[x] -= f;
        E[x ^ 1] += f;
        return f;
    }
    return 0;
}

ll maxflow(int src) {
    ll flow = 0;
    while (int f = dfs(src, inf)) {
        tim++;
        flow += f;
    }
    return flow;
}
