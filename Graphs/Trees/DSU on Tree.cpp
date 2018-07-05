// DSU on Tree or Smaller to Larger on Tree
// Solves subtrees recursively and then merges them by copying smaller to larger
// Complexity: (n * log n * X), X = Complexity of inserting an element into a used data structure
// Usage: [CF Educational 2] Lomsat gelral https://codeforces.com/contest/600/problem/E
//        [CF Round #316] Tree Requests https://codeforces.com/contest/570/problem/D
//        [CF Round #130] Blood Cousins https://codeforces.com/contest/208/problem/E

const int MAXN = 1e5 + 5;

set<int> S[MAXN];
vector<int> G[MAXN];

void Union(int a, int b)
{
    if (S[a].size() < S[b].size())
    {
         swap(S[a], S[b]);
    }
    for (auto i : S[b])
    {
         S[a].insert(i);
    }
    S[b].clear();
}

void dfs(int v, int p)
{
    S[v].insert(v);
    for (int u : G[v])
    {
        if (u == p) continue;
        dfs(u, v);
        Union(v, u);
    }
}
