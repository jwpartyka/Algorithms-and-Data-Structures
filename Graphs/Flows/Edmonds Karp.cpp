// Computes maxflow using Edmonds - Karp algorithm
// Complexity: O(V * E^2)
// Usage: [SPOJ] FLOW http://www.spoj.com/A12/problems/FLOW/
//        [VI POI] Speleology https://szkopul.edu.pl/problemset/problem/l7RiYCdarLZV51E2daTt4n4W/site/?key=statement
//        [XVIII POI] Programming Contest https://szkopul.edu.pl/problemset/problem/VwDLJhYqi1z_sZrb2NyfvQ5e/site/?key=statement
//        [XVII POI] Bridges https://szkopul.edu.pl/problemset/problem/gh2Yj6Ckrt4Lo_RojONuljuC/site/?key=statement

using ll = long long;

#define st first
#define nd second

const int MAXN = 5e3 + 5, inf = 1e9;

int E[MAXN * MAXN], vis[MAXN], tgt, id, tim = 1;
pair<int, int> p[MAXN];
vector<pair<int, int>> G[MAXN];

inline void addEdge(int a, int b, int c) {
    G[a].push_back({b, id});
    E[id++] = c;
    G[b].push_back({a, id++});
}

bool bfs(int src) {
    queue<pair<int, int>> Q;
    Q.push({src, inf});
    vis[src] = 0;
    while (not Q.empty()) {
        int v = Q.front().st, f = Q.front().nd;
        Q.pop();
        if (not f) {
            continue;
        }

        for (auto e : G[v]) {
            int u = e.st, x = e.nd;
            if (not E[x] or vis[u] == tim) {
                continue;
            }

            p[u] = {v, x};
            if (u == tgt) {
                return f;
            }
            vis[v] = tim;
            Q.push({u, min(f, E[x])});

        }
    }

    return 0;
}

ll maxflow(int src) {
    ll flow = 0;
    while (int f = bfs(src)) {
        int u = tgt;
        while (u != src) {
            int v = p[u].st, x = p[u].nd;
            E[x] -= f;
            E[x ^ 1] += f;
            u = v;
        }
        tim++;
        flow += f;
    }
    return flow;
}
