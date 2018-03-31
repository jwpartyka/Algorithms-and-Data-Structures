// Divides a graph into biconnected components using Tarjan's algorithm.
// Complexity: O(|V| + |E|)
// Usage: [XXIII POI] Niebanalne podroze https://szkopul.edu.pl/problemset/problem/YY6-3ua-C1rt7q-97laWc0UP/site/?key=statement
//        [PA 2015] Mały sabotaż w wielkim mieście https://sio2.mimuw.edu.pl/c/pa-2015-1/p/sab/
//        [Edu CF Round 10] Pursuit For Artifacts http://codeforces.com/problemset/problem/652/E
//        [VK Cup 2016 Round 1] Bear and Chemistry http://codeforces.com/problemset/problem/639/F

#define st first
#define nd second

const int MAXN = 1e6+5;

// id of the BC in which vertex v is, low function, preorder
int BC[MAXN], low[MAXN], pre[MAXN], num, tim;
bool vis[MAXN], used[MAXN]; // Visited vertices, used edges
pair<int, int> E[MAXN]; // List of edges (v, u)
vector<pair<int, int>> G[MAXN]; // Graph (u, id(v, u))
stack<int> St; // Stack of visited edges which are not yet in any BC


void dfs(int v, int p)
{
    vis[v] = 1, pre[v] = tim++, low[v] = pre[v];
    for (auto e : G[v])
    {
        int u = e.st, id = e.nd;
        if (u == p) continue;

        if (!used[id])
        {
            St.push(id);
            used[id] = 1;
        }

        if (!vis[u])
        {
            dfs(u, v);
            low[v] = min(low[v], low[u]);
            // If v is an articulation point then create a new BC with
            // edges from the top of the stack until (v, u)
            if (low[u] >= pre[v])
            {
                int x = St.top();
                while (x != id)
                {
                    BC[x] = num;
                    St.pop();
                    x = St.top();
                }
                BC[x] = num++;
                St.pop();
            }
        }
        else low[v] = min(low[v], pre[u]);
    }
}
