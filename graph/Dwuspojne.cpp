#define st first
#define nd second

const int MAXN = 1e6+5;

//BC[v] - numer dwuspójnej zawierającej v; funkcja low; numery preorder
int BC[MAXN], low[MAXN], pre[MAXN], num, tim;
bool vis[MAXN], used[MAXN]; //Odwiedzony wierzchołek; użyta krawędź
pair<int, int> E[MAXN]; //Lista krawędzi (v, u)
vector<pair<int, int>> G[MAXN]; //Graf (u, id(v, u))
stack<int> St; //Stos do wyznaczania dwuspójnych

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
            //Jeżeli v jest punktem artykulacji to dodaj do jednej dwuspójnej
            //wszystkie krawędzie z wierzchu stosu aż do (v, u) włącznie
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
