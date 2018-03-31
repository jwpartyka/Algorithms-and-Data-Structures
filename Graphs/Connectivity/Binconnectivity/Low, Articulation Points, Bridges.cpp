// 1) Computes low function for every vertex
// 2) Finds bridges
// 3) Finds articulation points
// Complexity: O(|V| + |E|)

//Usage: [XV OI] Blokada https://szkopul.edu.pl/problemset/problem/eDt8w290owtatmCjad0O0ywk/site/?key=statement
//       [KI] Mosty http://ki.staszic.waw.pl/task.php?name=mosty


#define st first
#define nd second

const int MAXN = 1e6+5;
int pre[MAXN], low[MAXN], tim; // preorder, low function,
bool vis[MAXN]; // visited vertices
vector<int> G[MAXN], points; // Graph, articulation points
vector<pair<int, int>> bridges; // Bridges

void calcLow(int v, int p)
{
    vis[v] = 1, pre[v] = tim++, low[v] = pre[v];
    bool ok = 0;
    for (int u : G[v])
    {
        if (u == p) continue;
        // 1)
        if (vis[u]) low[v] = min(low[v], pre[u]);
        else
        {
            calcLow(u, v);
            low[v] = min(low[v], low[u]);
        }

        // 2)
        if (low[u] > pre[v]) bridges.push_back({v, u});

        // 3)
        if (ok) continue;
        if (low[u] >= pre[v])
        {
            // If the root has only 1 child then it's not an articulation point
            if (v == 1 && G[v].size() == 1) continue;
            points.push_back(v);
            ok = 1;
        }
    }
}
