
// =============================
// 树上前缀和路径和查询模板
// 支持任意编号的树，支持多次查询祖先到子孙路径权值和
// =============================

#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 1000005;   // 最大节点数
int n, q;                   // n为节点数，q为查询数
int fuqin[MAXN];            // fuqin[i]表示i节点的父亲编号（根节点父亲为0）
long long qianzhuihe[MAXN]; // qianzhuihe[i]表示根到i路径上的权值和
vector<int> tree[MAXN];     // 邻接表存树结构，tree[u]存u的所有儿子
long long quanzhi[MAXN];    // quanzhi[i]表示i节点的权值

// 深度优先遍历递推qianzhuihe数组，保证父节点先于子节点被处理
// u: 当前遍历到的节点编号
void dfs(int u) // 深度优先搜索遍历 函数
{
    for (int v : tree[u]) // 遍历u的所有儿子
    {
        // 子节点的前缀和 = 父节点的前缀和 + 子节点权值
        qianzhuihe[v] = qianzhuihe[u] + quanzhi[v]; // 主操作
        dfs(v);                                     // 递归 处理子树
    }
}

int main()
{
    // 加速输入输出，防止大数据卡常
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> q; // 读入节点数和查询数
    fuqin[1] = 0;  // 根节点父亲设为0

    // 读入每个节点的父亲，并建树
    for (int i = 2; i <= n; i++)
    {
        cin >> fuqin[i];
        tree[fuqin[i]].push_back(i); // 把i挂到父亲下面
    }

    // 读入每个节点的权值
    for (int i = 1; i <= n; i++)
    {
        cin >> quanzhi[i];
    }

    // 初始化根节点的前缀和
    qianzhuihe[1] = quanzhi[1];
    // 从根节点出发递归计算所有节点的前缀和
    dfs(1);

    // 多次查询：每次给定a和b，a是b祖先，输出a到b路径权值和
    while (q--)
    {
        int a, b;
        cin >> a >> b;
        // 路径和 = qianzhuihe[b] - qianzhuihe[a] + quanzhi[a]（包含a和b）
        cout << qianzhuihe[b] - qianzhuihe[a] + quanzhi[a] << '\n';
    }
}
