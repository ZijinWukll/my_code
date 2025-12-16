#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int MAXN = 300005;
int n;
vector<int> a[MAXN]; // a[i][0]正面，a[i][1]反面

// 检查是否存在一种翻转区间，使得中位数 >= mid
bool check(int mid)
{
    vector<int> front(n + 1), back(n + 1), diff(n + 1);
    // 统计每张卡片正反面是否 >= mid
    for (int i = 1; i <= n; i++)
    {
        front[i] = (a[i][0] >= mid);
        back[i] = (a[i][1] >= mid);
        // 翻转第i张卡片时，贡献变化为 back[i] - front[i]
        diff[i] = back[i] - front[i];
    }
    int need = (n + 1) / 2; // 中位数需要的数量
    int base = 0;           // 不翻转时正面 >= mid 的数量
    for (int i = 1; i <= n; i++)
        base += front[i];
    // 如果不翻转就满足，直接返回true
    if (base >= need)
        return true;
    // 求diff的最大子段和，表示翻转哪个区间能让 >=mid 的卡牌数最多
    int max_add = 0, tempadd = 0; // 求翻转后的最大增量
    for (int i = 1; i <= n; i++)
    {
        tempadd = max(diff[i], tempadd + diff[i]); // 可能变多也可能变少
        max_add = max(max_add, tempadd);           // 更新最大增量
    }
    // 翻转后的最大贡献，具体是哪个区间其实并不重要
    if (base + max_add >= need)
        return true;
    return false;
}

int main()
{
    cin >> n;
    int min_val = 1e9, max_val = 0;
    for (int i = 1; i <= n; i++)
    {
        int zheng, fan;
        cin >> zheng >> fan;
        a[i].push_back(zheng);
        a[i].push_back(fan);
        min_val = min(min_val, min(zheng, fan));
        max_val = max(max_val, max(zheng, fan));
    }
    int left = min_val, right = max_val, ans = min_val;
    // 二分查找最大中位数
    while (left <= right)
    {
        int mid = left + (right - left) / 2; // 防止溢出
        if (check(mid))
        {
            ans = mid; // 可以达到，尝试更大
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    cout << ans << endl;
    return 0;
}

/*
代码说明：
1. check(mid)函数用最大子段和算法O(n)优化，求翻转区间带来的最大增量。
2. base为不翻转时正面>=mid的数量，diff为每张卡片翻转后贡献变化。
3. 主流程二分查找最大中位数，最终输出答案。
4. 所有变量类型均为int，数据范围安全。
5. 详细注释说明每步逻辑，便于初学者理解。
*/