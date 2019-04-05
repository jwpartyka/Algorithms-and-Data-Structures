// Computes maxflow using Dinic's algorithm.
// Complexity:
// 1) In a random graph: O(V^2 * E)
// 2) In graphs with unit distances: O(min{V^(2/3), E^(1/2)} * E)
// 3) In barpitite graphs: O(E * V^(1/2)))
// Usage: [SPOJ] FASTFLOW http://www.spoj.com/problems/FASTFLOW/
//        [VI POI] Speleology https://szkopul.edu.pl/problemset/problem/l7RiYCdarLZV51E2daTt4n4W/site/?key=statement
//        [XVIII POI] Programming Contest https://szkopul.edu.pl/problemset/problem/VwDLJhYqi1z_sZrb2NyfvQ5e/site/?key=statement
//        [XVII POI] Bridges https://szkopul.edu.pl/problemset/problem/gh2Yj6Ckrt4Lo_RojONuljuC/site/?key=statement

using ll = long long;

#define st first
#define nd second

const int MAXN = 5e3 + 5, inf = 1e9;

int E[MAXN * MAXN], dist[MAXN], n, tgt, id;
vector<pair<int, int>> G[MAXN], GL[MAXN];

inline void addEdge(int a, int b, int c) {
    G[a].push_back({b, id});
    E[id++] = c;
    G[b].push_back({a, id++});
}

bool bfs(int src) {
    for (int i = 0; i <= n; i++) {
        dist[i] = 0;
        GL[i].clear();
    }

    queue<int> Q;
    Q.push(src);
    dist[src] = 1;
    while (not Q.empty()) {
        int v = Q.front();
        Q.pop();

        for (auto e : G[v]) {
            int u = e.st, x = e.nd;
            if (not dist[u] and E[x]) {
                dist[u] = dist[v] + 1;
                Q.push(u);
            }

            if (dist[u] == dist[v] + 1) {
                GL[v].push_back({u, x});
            }
        }
    }

    return dist[tgt];
}

int dfs(int v, int flow) {
    if (v == tgt) {
        return flow;
    }

    for (int i = 0; i < GL[v].size(); i++) {
        auto e = GL[v][i];
        int u = e.st, x = e.nd;

        int f = E[x];
        if (f) {
            f = dfs(u, min(flow, f));
        }
        if (not f) {
            swap(GL[v][i], GL[v].back());
            GL[v].pop_back();
            i--;
            continue;
        }

        E[x] -= f;
        E[x ^ 1] += f;
        return f;
    }

    return 0;
}

ll dinic(int src) {
    ll flow = 0;
    while (bfs(src)) {
        while (int f = dfs(src, inf)) {
            flow += f;
        }
    }
    return flow;
}
