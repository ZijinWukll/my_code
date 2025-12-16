#include <iostream>
#include <vector>
#include <algorithm> // 用于sort排序函数
using namespace std;

int main()
{
    // 1. 读取输入的背包容量n和物品数量m
    int n, m;
    cin >> n >> m;

    // 2. 按物品容量分类存储价值（v=1存vec1，v=2存vec2）
    vector<int> v_1, v_2;
    for (int i = 0; i < m; i++)
    {
        int v, c; // 单个物品的容量v和价值c
        cin >> v >> c;
        if (v == 1)
        {
            v_1.push_back(c);
        }
        else if (v == 2)
        { // 题目保证v≤2，无需处理其他情况
            v_2.push_back(c);
        }
    }

    // 3. 对两类物品的价值从大到小排序（优先选价值高的）
    sort(v_1.rbegin(), v_1.rend()); // 反向迭代器实现从大到小排序
    sort(v_2.rbegin(), v_2.rend());

    // 4. 计算v=1物品的前缀和数组sum1
    int len1 = v_1.size();               // v=1物品的总数量
    vector<long long> sum1(len1 + 1, 0); // sum1[0]=0，sum1[1]~sum1[len1]为前缀和
    for (int i = 1; i <= len1; i++)
    {
        sum1[i] = sum1[i - 1] + v_1[i - 1]; // sum1[i] = 前i个v=1物品的总价值
    }

    // 5. 计算v=2物品的前缀和数组sum2
    int len2 = v_2.size();               // v=2物品的总数量
    vector<long long> sum2(len2 + 1, 0); // sum2[0]=0，sum2[1]~sum2[len2]为前缀和
    for (int i = 1; i <= len2; ++i)
    {
        sum2[i] = sum2[i - 1] + v_2[i - 1]; // sum2[i] = 前i个v=2物品的总价值
    }

    // 6. 枚举v=2物品的选择数量k，计算最大总价值
    long long max_ans = 0; // 存储最终答案（用long long避免价值总和溢出）
    // k的范围：0 ≤ k ≤ min(能选的v=2物品数, 背包能装的v=2物品数)
    int max_k = min(len2, n / 2); // 最多选max_k个v=2物品

    for (int k = 0; k <= max_k; k++)
    {
        int remain = n - 2 * k;                         // 选k个v=2物品后，剩余的背包容量（只能装v=1物品）
        int take1 = min(len1, remain);                  // 剩余容量能装的v=1物品数量（不超过总v=1物品数）
        long long currentvalue = sum2[k] + sum1[take1]; // 当前组合的总价值
        if (currentvalue > max_ans)
        {
            max_ans = currentvalue; // 更新最大价值
        }
    }

    // 7. 输出最终结果
    cout << max_ans << endl;

    return 0;
}

/*
算法思路
分类统计物品：将所有物品按容量分为两类，分别存储它们的价值：
vec1：存储所有容量v=1的物品价值。
vec2：存储所有容量v=2的物品价值。
价值排序：对两类物品价值 从大到小 排序，确保优先选择价值更高的物品（贪心思想，因同容量物品选价值高的更优）。
预处理前缀和：计算两类物品的前缀和数组，快速获取 “选前 k 个物品的总价值”：
sum1[k]：选vec1中前k个物品的总价值（sum1[0]=0，sum1[1]=vec1[0]，以此类推）。
sum2[k]：选vec2中前k个物品的总价值（同理）。
枚举最优组合：枚举选择v=2物品的数量k（最多选min(总v=2物品数, n//2)个），
则剩余容量可装v=1物品的数量为n-2*k，计算总价值并记录最大值。
*/
/*
排序的意义
对同容量物品按价值从大到小排序，是因为 “选同容量的物品时，价值高的优先选” 是局部最优解，
最终能导向全局最优解（此问题中贪心有效，因容量仅 1 或 2）。
前缀和的作用
若不预处理前缀和，每次计算 “选 k 个物品的总价值” 需循环累加，时间复杂度会升至O(n*m)；
前缀和数组可将此操作优化为O(1)，是降低时间复杂度的核心。
*/