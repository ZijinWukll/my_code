#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 1005;
vector<int> tree[N]; // 邻接表
int a[N];            // 权值
int n;
long long ans = 0;

// 按权值降序染色，children为父到子的有向树
vector<vector<int>> children;
void dfs2(int u, int t)
{
    ans += 1LL * t * a[u];
    vector<pair<int, int>> sons;
    for (int v : children[u])
    {
        sons.push_back({a[v], v});
    }
    sort(sons.rbegin(), sons.rend());
    for (auto &p : sons)
    {
        dfs2(p.second, t + 1);
    }
}

int main()
{
    cin >> n;
    for (int i = 1; i < n; ++i)
    {
        int x, y;
        cin >> x >> y;
        tree[x].push_back(y);
        tree[y].push_back(x);
    }
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    // 建立有向树（父到子），用parent数组记录父节点
    vector<int> parent(n + 1, 0);
    vector<bool> vis(n + 1, false);
    children.assign(n + 1, vector<int>()); // 存储父到子的有向树
    // BFS建父子关系
    vector<int> q = {1};
    vis[1] = true;
    for (int i = 0; i < q.size(); ++i)
    {
        int u = q[i];
        for (int v : tree[u])
        {
            if (!vis[v])
            {
                parent[v] = u;
                vis[v] = true;
                q.push_back(v);
                children[u].push_back(v); // 只保留父到子的边
            }
        }
    }
    // ...existing code...
    dfs2(1, 1);
    cout << ans << endl;
    return 0;
}
