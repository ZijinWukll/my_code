// 助教哥哥这题我真看不懂T_T
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int N = 1005; // 最大节点数

// 定义节点结构体
struct Node
{
    int id;      // 节点编号
    long long w; // 当前集合的总权值
    int s;       // 当前集合的大小（节点数）
    double avg;  // 平均权值 w/s
} nodes[N];

vector<int> tree[N]; // 邻接表存储树
int father[N];       // 记录每个节点的父节点
int p[N];            // 并查集数组，用于寻找集合的根
bool visited[N];     // 标记节点是否已被合并
int a[N];            // 初始权值
int n;               // 节点数量

// 并查集查找函数，带路径压缩
int find(int x)
{
    if (p[x] == x)
        return x;
    return p[x] = find(p[x]);
}

// DFS构建父子关系
void dfs(int u, int fa)
{
    father[u] = fa;
    for (int v : tree[u])
    {
        if (v != fa)
        {
            dfs(v, u);
        }
    }
}

int main()
{
    // 1. 输入处理
    if (!(cin >> n))
        return 0;

    // 读入边
    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    long long ans = 0; // 记录最小总代价

    // 读入权值并初始化
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        nodes[i].id = i;
        nodes[i].w = a[i];
        nodes[i].s = 1;
        nodes[i].avg = (double)a[i];
        p[i] = i;           // 并查集初始化
        visited[i] = false; // 初始都未合并
        ans += a[i];        // 初始代价（假设所有点都在第1个位置的累积，后续加上偏移代价）
    }

    // 构建树的父子关系，根节点为1
    dfs(1, 0);

    // 2. 贪心合并过程
    // 每次寻找平均权值最大的非根节点，将其合并到父节点所在的集合
    for (int i = 0; i < n - 1; i++)
    {
        int best_node = -1;
        double max_avg = -1.0;

        // 遍历所有节点，找到未被合并且平均权值最大的节点（排除根节点1）
        for (int j = 2; j <= n; j++)
        {
            if (!visited[j])
            { // 如果j是某个集合的根
                if (nodes[j].avg > max_avg)
                {
                    max_avg = nodes[j].avg;
                    best_node = j;
                }
            }
        }

        if (best_node == -1)
            break;

        int u = best_node;
        // 找到 u 的父节点所在的集合根
        int fa = father[u];
        int root_fa = find(fa);

        // 更新总代价
        // 将集合 u 接在集合 root_fa 后面，u 中所有点的时间延后 root_fa 的大小
        ans += nodes[u].w * nodes[root_fa].s;

        // 合并节点信息到父集合
        nodes[root_fa].w += nodes[u].w;
        nodes[root_fa].s += nodes[u].s;
        nodes[root_fa].avg = (double)nodes[root_fa].w / nodes[root_fa].s;

        // 在并查集中合并，并标记 u 已处理
        p[u] = root_fa;
        visited[u] = true;
    }

    // 3. 输出结果
    cout << ans << endl;

    return 0;
}
/*
这是一个非常经典的贪心问题，通常被称为“树上染色”问题（Color a Tree）。为了让你更透彻地理解，我将解题思路拆解得更详细，就像是在手动模拟这个过程一样。

### 详细解题思路

#### 1. 问题的核心矛盾
*   **目标**：最小化总代价 $\sum (T_i \times a_i)$。其中 $T_i$ 是第 $i$ 个点被染色的次序（第几个被染），$a_i$ 是它的权值。
*   **直觉**：为了让总和最小，我们希望权值 $a_i$ 越大的点，对应的次序 $T_i$ 越小（即越早被染色）。
*   **约束**：一个点染色前，它的父节点必须先染色。这意味着我们不能简单地把所有点按权值排序，必须遵循树的拓扑结构。

#### 2. 引入“等效权值”的概念
假设我们有两个节点（或节点集合）：
*   集合 $A$：总权值 $W_A$，包含节点数 $S_A$。
*   集合 $B$：总权值 $W_B$，包含节点数 $S_B$。

如果我们可以自由决定先染 $A$ 还是先染 $B$（假设它们互不依赖），哪种顺序更优？
*   **先 A 后 B** 的代价：$A$ 的代价 + $B$ 的代价（$B$ 的时间被推迟了 $S_A$）。
    *   代价 1 = $Cost(A) + (Cost(B) + W_B \times S_A)$
*   **先 B 后 A** 的代价：$B$ 的代价 + $A$ 的代价（$A$ 的时间被推迟了 $S_B$）。
    *   代价 2 = $Cost(B) + (Cost(A) + W_A \times S_B)$

比较两者：
如果 **代价 1 < 代价 2**，即 $W_B \times S_A < W_A \times S_B$，移项得：
$$ \frac{W_B}{S_B} < \frac{W_A}{S_A} $$
**结论**：**平均权值（$\frac{W}{S}$）越大**的集合，应该越先被染色。

#### 3. 贪心策略的具体执行
基于上面的结论，我们发现：**树中平均权值最大的那个节点 $u$（非根节点），一旦它的父节点 $fa$ 被染色了，紧接着立刻染色 $u$ 一定是最优的。**

这就好比 $u$ 和 $fa$ 变成了“连体婴”，我们可以把 $u$ 合并进 $fa$ 里。

#### 4. 详细操作步骤（模拟算法流程）

**初始状态**：
每个点都是一个独立的集合。
*   集合权值 $W_i = a_i$
*   集合大小 $S_i = 1$
*   平均权值 $Avg_i = a_i$
*   总代价 $Ans = \sum (a_i \times 1)$ （这里先假设所有点都在第1秒染色，后面合并时再补上推迟的代价，这是一种计算技巧，也可以按常规方法算）。

**循环步骤**（直到只剩根节点）：

1.  **寻找最大值**：
    在所有**未被合并**且**非根**的节点中，找到平均权值 $Avg$ 最大的节点，记为 $u$。
    *   如果有多个最大值，任选一个即可。

2.  **定位父集合**：
    找到 $u$ 的父节点 $fa$。注意，因为 $fa$ 可能之前已经被合并到了它的父节点里，所以我们需要用**并查集**（或者类似追踪链表的方法）找到 $fa$ 当前所在的集合的根节点，记为 $root\_fa$。

3.  **计算合并代价（关键点）**：
    当我们把 $u$ 接在 $root\_fa$ 后面时，意味着 $u$ 集合里的所有节点，染色顺序都不得不往后推迟 $S_{root\_fa}$ 位（因为 $root\_fa$ 里的点要先染）。
    *   新增代价 = $W_u \times S_{root\_fa}$
    *   将这个代价加到总结果 $Ans$ 中。

4.  **执行合并**：
    将 $u$ 合并入 $root\_fa$：
    *   新总权值：$W_{root\_fa} = W_{root\_fa} + W_u$
    *   新总大小：$S_{root\_fa} = S_{root\_fa} + S_u$
    *   新平均权值：$Avg_{root\_fa} = \frac{W_{root\_fa}}{S_{root\_fa}}$
    *   标记 $u$ 已经被合并（从可选列表中移除）。
    *   更新树结构：$u$ 的所有子节点的父节点逻辑上变成了 $root\_fa$（通过并查集实现）。

#### 5. 举例说明
假设树结构：1 -> 2, 1 -> 3。权值：$a_1=1, a_2=2, a_3=5$。
*   初始：
    *   节点1: $W=1, S=1, Avg=1$
    *   节点2: $W=2, S=1, Avg=2$
    *   节点3: $W=5, S=1, Avg=5$
    *   基础代价 $Ans = 1+2+5 = 8$ (假设都在第1位)

*   **第一轮**：
    *   找最大 Avg：节点3 ($Avg=5$) 最大。
    *   父节点：1。
    *   代价增加：$W_3 \times S_1 = 5 \times 1 = 5$。$Ans = 8 + 5 = 13$。
    *   合并 3 到 1：
        *   节点1新状态: $W=1+5=6, S=1+1=2, Avg=3$。
        *   节点3标记已合并。

*   **第二轮**：
    *   找最大 Avg（非根）：只剩节点2 ($Avg=2$)。
    *   父节点：1。
    *   代价增加：$W_2 \times S_1 = 2 \times 2 = 4$。$Ans = 13 + 4 = 17$。
    *   合并 2 到 1：
        *   节点1新状态: $W=6+2=8, S=2+1=3, Avg=2.66$。
    *   结束。

*   最终答案：17。
    *   验证顺序：1 -> 3 -> 2。
    *   代价：$1\times1 + 5\times2 + 2\times3 = 1 + 10 + 6 = 17$。正确。

这个思路的核心在于**局部最优导致全局最优**，通过不断合并“性价比”最高的节点，最终得到最小代价。
*/