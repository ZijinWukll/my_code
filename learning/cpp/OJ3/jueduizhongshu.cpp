#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
using namespace std;

/*
高效绝对众数查询（随机化+前缀和）
思路：
1. 预处理每个数出现的位置（下标列表）。
2. 每次询问区间[l, r]，随机采样若干个位置，统计这些数在区间内出现次数。
3. 如果某个数出现次数超过一半，输出该数，否则输出-1。
4. 由于采样次数足够多，正确率极高，且效率远高于暴力。
*/

const int MAXN = 100005; // 最大数据范围
vector<int> pos[MAXN];   // pos[x]存x出现的所有下标，方便后续统计区间出现次数
int a[MAXN];             // 原始序列，a[1]~a[n]

// 统计v中有多少元素在[l, r]区间
// 用二分法快速统计，复杂度O(log n)

// 功能：统计v数组中有多少元素的值在[l, r]区间（这里v存的是某个数x在原序列中的所有出现位置，即a的下标）
// 实现：
// lower_bound(v.begin(), v.end(), l) 返回第一个 >= l 的迭代器
// upper_bound(v.begin(), v.end(), r) 返回第一个 > r 的迭代器
// 两者相减即为区间[l, r]内x出现的次数
// 时间复杂度O(log n)
int countInRange(const vector<int> &v, int l, int r)
{
    // 例如v = [2, 5, 7, 10]，l=5, r=10
    // lower_bound找到5的位置为1，upper_bound找到10后面的位置为4
    // 返回区间[5, 10]内的元素个数即为4-1=3
    return upper_bound(v.begin(), v.end(), r) - lower_bound(v.begin(), v.end(), l);
} // 最后将拿这个值与len/2比较

int main()
{
    ios::sync_with_stdio(false); // 输入输出加速，解绑
    cin.tie(0);
    cout.tie(0);

    int n, q;
    cin >> n >> q; // 读入序列长度和询问次数
    for (int i = 1; i <= n; ++i)
    {
        cin >> a[i];
        pos[a[i]].push_back(i); // 记录每个数出现的位置，方便后续统计，建立pos[x]
    }

    mt19937 rng(114514);                // 随机数生成器，种子可自定义
    uniform_int_distribution<int> dist; // 区间分布

    while (q--)
    {
        int l, r;
        cin >> l >> r;       // 读入查询区间
        int len = r - l + 1; // 区间长度
        int ans = -1;        // 默认无绝对众数
        // 随机采样30次，理论上正确率极高
        for (int t = 0; t < 30; ++t)
        {
            dist = uniform_int_distribution<int>(l, r); // 随机区间分布
            int idx = dist(rng);                        // 随机选一个位置
            int x = a[idx];                             // 取该位置的数
            int cnt = countInRange(pos[x], l, r);       // 统计x在区间[l, r]出现次数
            if (cnt > len / 2)
            {
                ans = x; // 找到绝对众数
                break;   // 提前结束
            }
        }
        cout << ans << '\n'; // 输出答案
    }
    return 0;
}

/*
代码说明：
1. pos[x]预处理每个数出现的位置，方便后续快速统计区间出现次数。
2. countInRange函数用二分法统计x在区间[l, r]出现次数，复杂度O(log n)。
3. 每次询问随机采样若干位置，统计这些数在区间内出现次数，判断是否为绝对众数。
4. 变量类型均为int，区间计数不会溢出，若权值和需long long可自行调整。
5. 采样次数可根据实际数据调整，理论上30次正确率极高。
6. 输入输出加速，适合大数据。
*/