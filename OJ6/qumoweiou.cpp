#include <iostream>
using namespace std;
typedef long long ll;
int T;
ll a[100005] = {0};
int ans[100005];
int solve(int n, ll *a)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if ((a[j] % a[i]) % 2 == 0)
            {
                return 1;
            }
        }
    }
    return -1;
}
int main()
{
    cin >> T;
    for (int i = 0; i < T; i++)
    {
        int n;
        cin >> n;
        for (int j = 0; j < n; j++)
        {
            cin >> a[j];
        }
        ans[i] = solve(n, a);
    }
    for (int i = 0; i < T; i++)
    {
        cout << ans[i] << endl;
    }
    return 0;
}