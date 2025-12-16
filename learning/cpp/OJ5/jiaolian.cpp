// 三人篮球分组最大进攻值问题，状态压缩DP解法
#include <iostream>
#include <algorithm>
using namespace std;
int n;                       // 球员人数
int moqi[21][21];            // moqi[i][j]：i号与j号球员的默契值
int danda[21];               // danda[i]：i号球员的单打能力值
long long zudui[21][21][21]; // zudui[i][j][k]：三人组(i,j,k)的最大进攻值
long long dp[1 << 21];       // dp[mask]：分组状态mask下的最大进攻值

// 计算三人组(i,j,k)的最大进攻值
// 包括三种战术：单打、挡拆、三人传切，取最大
long long jingongmax(int i, int j, int k)
{
    long long dan = max({danda[i], danda[j], danda[k]}); // 三人单打能力最大值
    // 挡拆：所有两人组合的默契值最大值（共6种）
    long long shuang = max({moqi[i][j], moqi[j][i], moqi[i][k], moqi[k][i], moqi[j][k], moqi[k][j]});
    // 三人传切：三人间默契值乘积
    long long san = 1LL * moqi[i][j] * moqi[i][k] * moqi[j][k];
    return max({dan, shuang, san}); // 返回三种战术的最大值
}

// 预处理所有三人组的最大进攻值，存入zudui数组
void preprocess()
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                if (i != j && i != k && j != k)
                    zudui[i][j][k] = jingongmax(i, j, k);
}

// 状态压缩DP，枚举所有分组方式，求最大进攻值
long long DP()
{
    int max_mask = 1 << n;      // 所有分组状态的总数（2^n）
    fill(dp, dp + max_mask, 0); // 初始化DP数组
    // mask：用二进制表示哪些球员已分组，1表示已分组，0表示未分组
    for (int mask = 0; mask < max_mask; mask++)
    {
        int bianhao[21], shuliang = 0; // bianhao存未分组球员编号，shuliang为数量
        for (int i = 0; i < n; i++)
            if (!(mask & (1 << i)))
                bianhao[shuliang++] = i;
        if (shuliang < 3)
            continue; // 剩余球员不足3人，无法再分组
        // 枚举所有未分组球员的三人组合
        for (int a = 0; a < shuliang; a++)
            for (int b = a + 1; b < shuliang; b++)
                for (int c = b + 1; c < shuliang; c++)
                {
                    // newmask：分组后新状态
                    int newmask = mask | (1 << bianhao[a]) | (1 << bianhao[b]) | (1 << bianhao[c]);
                    // 状态转移：更新新状态的最大进攻值
                    dp[newmask] = max(dp[newmask], dp[mask] + zudui[bianhao[a]][bianhao[b]][bianhao[c]]);
                }
    }
    // 返回所有球员都分组时的最大进攻值
    return dp[max_mask - 1];
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n; // 输入球员人数
    if (n % 3 != 0)
    {
        cout << 0 << endl; // 人数不是3的倍数，无法分组，输出0
        return 0;
    }
    for (int i = 0; i < n; i++)
        cin >> danda[i]; // 输入每个球员的单打能力
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> moqi[i][j]; // 输入每对球员的默契值

    preprocess();         // 预处理所有三人组最大进攻值
    long long ans = DP(); // 状态压缩DP求解最大进攻值
    cout << ans << endl;  // 输出答案
    return 0;
}