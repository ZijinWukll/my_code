#include <iostream>
using namespace std;

typedef long long ll;

ll solve(ll n, ll k)
{
    if (n == 0)
        return 0;
    if (k == 1)
        return n; // k=1特殊情况
    if (n < k)
        return n * (n + 1) / 2; // 所有都不能被k整除
    ll count = n / k;           // 能被k整除的个数
    ll result = 0;
    // 不能被k整除的部分
    ll remain = n - count;

    ll sum1 = (n + 1) * n / 2 - k * count * (count + 1) / 2;
    result += sum1;
    // 能被k整除的部分，递归
    result += solve(count, k);
    return result;
}

int main()
{
    ll n, k;
    cin >> n >> k;
    cout << solve(n, k) << endl;
    return 0;
}
