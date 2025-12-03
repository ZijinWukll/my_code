#include <iostream>
typedef long long ll;
using namespace std;
const int mod = 1000000007;
ll F(ll n)
{
    if (n == 0)
        return 0;
    if (n % 4 == 0)
        return ((n / 2) % mod) * ((n + 4) / 2 % mod) % mod;
    else if (n % 4 == 1)
        return ((n + 1) / 2 % mod) * ((n + 1) / 2 % mod) % mod;
    else if (n % 4 == 2)
        return ((n + 2) / 2 % mod) * ((n + 2) / 2 % mod) % mod;
    else
        return ((n + 1) / 2 % mod) * ((n + 1) / 2 % mod) % mod;
}
int main()
{
    int T;
    ll arr[105][2];
    cin >> T;
    for (int i = 0; i < T; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            cin >> arr[i][j];
        }
    }
    for (int i = 0; i < T; i++)
    {
        ll answer = F(arr[i][1]) - F(arr[i][0] - 1);

        cout << (answer + mod) % mod << " ";
    }
    return 0;
}
