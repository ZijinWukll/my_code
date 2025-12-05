#include <iostream>
#include <algorithm>
using namespace std;
int dp[105][1005];
int k, N;

int DP(int k, int N)
{
    dp[1][1] = 1;
    for (int i = 1; i <= k; i++)
        dp[i][0] = 0, dp[i][1] = 1;
    for (int j = 1; j <= N; j++)
        dp[1][j] = j;

    for (int i = 2; i <= k; i++)
    {
        for (int j = 2; j <= N; j++)
        {
            dp[i][j] = N + 1;
            for (int x = 1; x <= j; x++)
            {
                dp[i][j] = min(dp[i][j], 1 + max(dp[i - 1][x - 1], dp[i][j - x]));
            }
        }
    }
    return dp[k][N];
}
int main()
{
    cin >> N >> k;
    int ans = DP(k, N);
    cout << ans << endl;
    return 0;
}