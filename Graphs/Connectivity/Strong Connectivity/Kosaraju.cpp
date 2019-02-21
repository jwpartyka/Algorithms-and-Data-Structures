// Divides a graph into strongly connected components using Kosaraju's algorithm.
// 1) Creates a transpose graph and computes postorder numbers of each vertex
// 2) Processes vertices of the original graph in reverse postorder from 1)
// Complexity: O(|V| + |E|)
// Usage: [III POI] Agents https://szkopul.edu.pl/problemset/problem/lLzgarYSJUxLS5UXJHeyHl7U/site/?key=statement
//        [XIII POI] Professor Szu https://szkopul.edu.pl/problemset/problem/EijIYL4qkxxGJGHaVVnvdmgY/site/?key=statement

const int MAXN = 1e6+5;

int SCC[MAXN], nr; //SCC[v] - id of the SCC containing vertex v
bool vis[MAXN]; // Visited vertices
// Graph, transpose graph, graph of SCC:
vector<int> G[MAXN], Gt[MAXN], Gscc[MAXN];
stack<int> St; // Stack containing reverse postorder

void dfs(int v) {
    vis[v] = 1;
    for (int u : Gt[v]) {
        if (!vis[u]) {
            dfs(u);
        }
    }
    St.push(v);
}

void findSCC(int v) {
    vis[v] = 1, SCC[v] = nr;
    for (int u : G[v]) {
        if (vis[u]) {
            if (SCC[v] != SCC[u]) {
                Gscc[SCC[v]].push_back(SCC[u]);
            }
            continue;
        }
        findSCC(u);
    }
}

void addEdge(int a, int b) {
    // Adds edge (a, b) to the graph
    G[a].push_back(b);
    // Adds edge (b, a) to the transpose graph
    Gt[b].push_back(a);
}

void sccBuild(int n) {
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            dfs(i);
        }
    }

    fill(vis, vis + n + 1, 0);
    while (!St.empty()) {
        int v = St.top();
        St.pop();

        if (!vis[v]) {
            findSCC(v);
            nr++;
        }
    }
}
