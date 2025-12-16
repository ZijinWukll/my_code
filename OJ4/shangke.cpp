#include <iostream>
#include <vector>    // 用于存储课程列表（动态数组，适合不确定大小的场景）
#include <algorithm> // 用于排序函数 sort()

using namespace std; // 简化代码，避免每次写 std::

// 定义一个结构体（类似“模板”），存储单门课程的开始时间和结束时间
struct Course
{
    int start; // 课程开始时间 a_i
    int end;   // 课程结束时间 b_i
};

// 自定义排序规则：按课程结束时间升序排列（用于 sort 函数）
// 参数是两个 Course 类型的对象，返回 true 表示 left 应排在 right 前面
bool compareCourses(const Course &left, const Course &right)
{
    return left.end < right.end; // 结束时间小的在前
}

int main()
{
    // 1. 输入课程数量 n
    int n;
    cin >> n;

    // 2. 存储所有课程：用 vector 动态数组，避免固定数组的大小限制（适配 n 最大 1e6 的情况）
    vector<Course> courses(n); // 创建能容纳 n 个 Course 的 vector
    for (int i = 0; i < n; ++i)
    {
        // 输入第 i 门课的开始时间和结束时间，存入对应的 Course 对象
        cin >> courses[i].start >> courses[i].end;
    }

    // 3. 对课程按结束时间升序排序（贪心算法的核心步骤）
    sort(courses.begin(), courses.end(), compareCourses);

    // 4. 遍历课程，统计最多可选课程数
    int maxCount = 0;     // 记录最多可选课程数量，初始为 0
    int lastEndTime = -1; // 记录已选课程的“最后结束时间”，初始为 -1（因 a_i ≥ 0，确保第一门课必选）

    for (const auto &course : courses)
    { // 范围 for 循环：遍历所有课程（更简洁）
        // 若当前课程的开始时间 ≥ 已选课程的最后结束时间（无冲突）
        if (course.start >= lastEndTime)
        {
            maxCount++;               // 选择该课程，数量加 1
            lastEndTime = course.end; // 更新最后结束时间为当前课程的结束时间
        }
    }

    // 5. 输出结果
    cout << maxCount << endl;

    return 0;
}

/*
一、解题思路详解
贪心策略选择依据：要选最多课程，关键是让每门课 “占用时间尽可能短”，而 “结束时间早” 是实现这一点的最佳标准
—— 结束早意味着后续有更多时间选择其他课程。
例如：若有课程 [0,2]、[1,3]、[2,4]，优先选 [0,2]（结束最早），后续还能选 [2,4]，共 2 门；
若选 [1,3]，后续无课可选，仅 1 门。
具体步骤：
步骤 1：输入课程数量 n 和所有课程的开始时间 a_i、结束时间 b_i。
步骤 2：对所有课程按结束时间 b_i 升序排序（核心操作，确保优先选结束早的课）。
步骤 3：遍历排序后的课程，记录已选课程的 “最后结束时间”，若当前课程的开始时间 ≥ 最后结束时间（无冲突），则选择该课程，并更新最后结束时间。
步骤 4：统计选择的课程总数，输出结果。
*/
/*
排序规则 compareCourses
这是一个自定义比较函数，用于 sort 函数排序。
sort 函数默认按 “从小到大” 排序，但需要知道 “比较什么”—— 这里通过 compareCourses 告诉 sort：
比较两个课程的 end（结束时间）。
*/