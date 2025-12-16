#include <iostream>
#include <vector>
using namespace std;

// 检查是否可以将所有工程分成k段，每段的总时间不超过maxWork
// t：每个工程所需时间的数组
// n：工程数量
// k：工人数
// maxWork：每个工人能承受的最大连续工作时间，也就是T
bool check(const vector<int> &t, int n, int k, long long maxWork)
{                      // &表示引用主函数里的t
    int workers = 1;   // 当前已经分配的工人数，初始为1
    long long sum = 0; // 当前工人已分配的工作总时间
    for (int i = 0; i < n; ++i)
    {
        if (t[i] > maxWork)
            return false; // 如果某项工程本身就超过maxWork，则不可能分配
        if (sum + t[i] > maxWork)
        {
            // 当前工人分配满了，必须换下一个工人
            workers++;
            sum = t[i]; // 新工人开始分配当前工程
        }
        else
        {
            sum += t[i]; // 当前工人继续分配工程
        }
    }
    // 如果所需工人数不超过k，则分配方案可行
    return workers <= k;
}

int main()
{
    int n, k;
    cin >> n >> k;    // 读入工程数量和工人数
    vector<int> t(n); // 存储每个工程所需时间
    for (int i = 0; i < n; ++i)
    {
        cin >> t[i]; // 读入每项工程的时间
    }

    // 二分查找答案，left为最大单项工程时间，right为所有工程总时间
    long long left = 0, right = 0;
    for (int i = 0; i < n; ++i)
    {
        left = max(left, (long long)t[i]); // left至少为最大单项工程
        right += t[i];                     // right为所有工程总时间
    }

    // 二分查找最小可行的工人最大工作时间，开区间
    while (left < right)
    {
        long long mid = (left + right) / 2; // 当前尝试的最大工作时间
        if (check(t, n, k, mid))
        {
            // 如果可以分配，尝试更小的最大工作时间
            right = mid;
        }
        else
        {
            // 如果不可以分配，增大最大工作时间
            left = mid + 1;
        }
    }

    cout << left << endl; // 输出最小的最大工作时间
    return 0;
}

/*
代码说明：
1. check函数用于判断在最大工作时间maxWork下，能否用k个工人完成所有工程。
2. 主流程用二分法查找最小可行的最大工作时间。
3. 输入输出均为标准格式，适合初学者理解。
4. &表示引用，避免复制数组，提高效率。
*/