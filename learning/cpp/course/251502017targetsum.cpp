#include <iostream>
#include <vector>
using namespace std;

int dfs(const vector<int> &nums, int idx, int sum, int target)
{
    if (idx == nums.size())
    {
        return sum == target ? 1 : 0;
    }

    return dfs(nums, idx + 1, sum + nums[idx], target) + dfs(nums, idx + 1, sum - nums[idx], target);
}

int findans(vector<int> &nums, int target)
{
    return dfs(nums, 0, 0, target);
}

int main()
{
    int target;
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> nums[i];
    }
    cin >> target;
    cout << findans(nums, target) << endl;
    return 0;
}