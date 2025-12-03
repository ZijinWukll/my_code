#include <iostream>
#include <vector>
#include <algorithm> // 用于 sort 函数

using namespace std;

// 定义题目结构体：存储耗时 t 和难度系数 c
struct Problem
{
    int t; // 做题耗时（≤100）
    int c; // 难度系数（≤100）
};

// 排序规则函数：实现临项交换推导的最优顺序
// 当 a.t*b.c < b.t*a.c 时，a 排在 b 前面
bool compare(const Problem &a, const Problem &b)
{
    // 用 long long 计算避免乘法溢出（100*100=1e4，实际不会溢出，但养成习惯）
    return (long long)a.t * b.c < (long long)b.t * a.c;
}

int main()
{
    // 1. 读取输入数据
    ios::sync_with_stdio(false); // 关闭同步，加速输入（处理 1e6 数据必备）
    cin.tie(nullptr);            // 解除 cin 与 cout 的绑定，进一步加速

    int n; // 题目数量
    cin >> n;

    vector<Problem> problems(n); // 存储所有题目
    long long T = 0;             // 总时间 T = sum(t_i)，用 long long 避免溢出

    for (int i = 0; i < n; ++i)
    {
        cin >> problems[i].t >> problems[i].c;
        T += problems[i].t; // 累加计算总时间
    }

    // 2. 按最优规则排序题目
    sort(problems.begin(), problems.end(), compare);

    // 3. 计算最大总得分
    long long ans = 0;    // 总得分，用 long long 存储（防止溢出）
    long long remain = T; // 当前剩余时间（初始为总时间）

    for (const auto &p : problems)
    {                        // 遍历排序后的题目
        ans += remain * p.c; // 累加当前题目的得分
        remain -= p.t;       // 做完题目，剩余时间减少
    }

    // 4. 输出结果
    cout << ans << endl;

    return 0;
}

/*
最优顺序推导（临项交换法）
假设只有两道题 A(t1, c1) 和 B(t2, c2)，总时间为 T：
顺序 1：A 在前，B 在后
A 的得分：T * c1（初始剩余时间 T）
做完 A 后剩余时间：T - t1
B 的得分：(T - t1) * c2
总得分：T*c1 + (T-t1)*c2 = T*(c1+c2) - t1*c2
顺序 2：B 在前，A 在后
B 的得分：T * c2
做完 B 后剩余时间：T - t2
A 的得分：(T - t2) * c1
总得分：T*c2 + (T-t2)*c1 = T*(c1+c2) - t2*c1
比较两种顺序：要让顺序 1 更优，需满足：T*(c1+c2) - t1*c2 > T*(c1+c2) - t2*c1
化简后得：t1*c2 < t2*c1
即：当 t1*c2 < t2*c1 时，A 应排在 B 前面，这就是我们的排序规则。
*/